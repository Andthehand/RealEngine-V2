#include "ScriptEngine.h"

#include "ScriptGlue.h"
#include "RealEngine/Core/Project.h"

#include <Coral/TypeCache.hpp>
#include <Coral/GC.hpp>

namespace RealEngine {
	namespace Utils {
		static HashMap<std::string, ScriptFieldType> s_ScriptFieldTypeMap = {
			{ "System.Single", ScriptFieldType::Float },
			{ "System.Double", ScriptFieldType::Double },
			{ "System.Boolean", ScriptFieldType::Bool },
			{ "System.String", ScriptFieldType::String },
			{ "System.Char", ScriptFieldType::Char },
			{ "System.Int16", ScriptFieldType::Short },
			{ "System.Int32", ScriptFieldType::Int },
			{ "System.Int64", ScriptFieldType::Long },
			{ "System.Byte", ScriptFieldType::Byte },
			{ "System.UInt16", ScriptFieldType::UShort },
			{ "System.UInt32", ScriptFieldType::UInt },
			{ "System.UInt64", ScriptFieldType::ULong },

			{ "RealEngine.Color", ScriptFieldType::Color },

			{ "System.Numerics.Vector2", ScriptFieldType::Vector2 },
			{ "System.Numerics.Vector3", ScriptFieldType::Vector3 },
			{ "System.Numerics.Vector4", ScriptFieldType::Vector4 },

			{ "RealEngine.Entity", ScriptFieldType::Entity },
		};

		static void OnAppAssemblyFileSystemEvent(const std::filesystem::path& path, const filewatch::Event change_type) {
			RE_PROFILE_FUNCTION();

			if (change_type == filewatch::Event::modified) {
				Application::Get().SubmitToMainThread([]() {
					Project::GetScriptEngine()->ReloadAssembly();

					RE_CORE_INFO("Reloaded script assembly due to file change.");
				});
			}
		}
	}

	static void ExceptionCallback(std::string_view InMessage) {
		RE_CORE_ASSERT(false, "Unhandled native exception: {0}", InMessage);
	}

	static void DefaultMessageCallback(std::string_view InMessage, Coral::MessageLevel InLevel) {
		switch (InLevel) {
			case Coral::MessageLevel::Trace:
				RE_CORE_TRACE("{0}", InMessage);
				break;
			case Coral::MessageLevel::Info:
				RE_CORE_INFO("{0}", InMessage);
				break;
			case Coral::MessageLevel::Warning:
				RE_CORE_WARN("{0}", InMessage);
				break;
			case Coral::MessageLevel::Error:
				RE_CORE_ERROR("{0}", InMessage);
				break;
			default:
				RE_CORE_ASSERT(false, "Unknown message level!");
				break;
		}
	}

	ScriptEngine::ScriptEngine(const std::filesystem::path& scriptFile) {
		RE_PROFILE_FUNCTION();
		m_AssemblyFile = scriptFile;

		Coral::HostSettings settings = {
			.CoralDirectory = m_AssemblyFile.parent_path(),
			.MessageCallback = DefaultMessageCallback,
			.MessageFilter = Coral::MessageLevel::All,
			.ExceptionCallback = ExceptionCallback
		};

		if (!s_CoralInstance.IsInitialized()) {
			if (s_CoralInstance.Initialize(settings) != Coral::CoralInitStatus::Success) {
				RE_CORE_ASSERT(false, "Coral failed to initialize");
				return;
			}
		}

		m_AssemblyWatcher = CreateScope<filewatch::FileWatch<std::filesystem::path>>(m_AssemblyFile, Utils:: OnAppAssemblyFileSystemEvent);

		ReloadAssembly();
	}

	ScriptEngine::~ScriptEngine() {
		RE_PROFILE_FUNCTION();

		s_CoralInstance.UnloadAssemblyLoadContext(m_AppLoadContext);
		// Don't shutdown Coral here as there may be other ScriptEngine instances
		// s_CoralInstance.Shutdown();
	}

	void ScriptEngine::ReloadAssembly() {
		RE_PROFILE_FUNCTION();

		// Collect garbage before reloading to clean up old references
		UpdateGC();

		// Unload the current assembly load context
		s_CoralInstance.UnloadAssemblyLoadContext(m_AppLoadContext);

		// Create a new assembly load context
		m_AppLoadContext = s_CoralInstance.CreateAssemblyLoadContext("AppContext");

		// Load RealEngine assembly first to register internal calls
		std::filesystem::path realEngineAssemblyPath = m_AssemblyFile.parent_path() / "RealEngine.dll";
		Coral::ManagedAssembly& realEngineAssembly = m_AppLoadContext.LoadAssembly(realEngineAssemblyPath.string());
		ScriptGlue::RegisterFunctions(realEngineAssembly);

		m_Assembly = m_AppLoadContext.LoadAssembly(m_AssemblyFile.string());
	}

	void ScriptEngine::UpdateGC() {
		RE_PROFILE_FUNCTION();

		Coral::GC::Collect();
		Coral::GC::WaitForPendingFinalizers();
	}

	Scope<ScriptInstance> ScriptEngine::CreateObject(UUID entityID, std::string_view className) {
		RE_PROFILE_FUNCTION();

		Coral::Type& entityType = m_Assembly.GetType(className);
		if (entityType) {
			Coral::ManagedObject entityObject = entityType.CreateInstance((uint64_t)entityID);

			Scope<ScriptInstance> instance = CreateScope<ScriptInstance>(std::move(entityObject));
			instance->InvokeOnCreate();

			return instance;
		}
		else {
			RE_CORE_ERROR("Failed to create script object of class '{0}' - class not found! (Maybe Renamed?)", className);

			return Scope<ScriptInstance>(nullptr);
		}
	}

	std::vector<std::string> ScriptEngine::GetValidScriptClasses() {
		RE_PROFILE_FUNCTION();

		std::vector<std::string> classNames;
		Coral::Type entityType = *Coral::TypeCache::Get().GetTypeByName("RealEngine.Entity");

		for (const Coral::Type* type : m_Assembly.GetTypes()) {
			if (type->IsSubclassOf(entityType)) {
				classNames.push_back(std::string(type->GetFullName()));
			}
		}

		return classNames;
	}

	HashMap <std::string, std::vector<ScriptField>> ScriptEngine::GetAllClassFields() {
		HashMap <std::string, std::vector<ScriptField>> fieldMap;

		std::vector<std::string> classes = GetValidScriptClasses();
		for (const auto& className : classes) {
			Coral::Type& type = m_Assembly.GetType(className);

			auto fields = type.GetFields();
			std::vector<ScriptField> fieldsVector;
			for (auto& field : fields) {
				Coral::TypeAccessibility accessibility = field.GetAccessibility();
				
				if (accessibility == Coral::TypeAccessibility::Public) {
					if (Utils::s_ScriptFieldTypeMap.contains(field.GetType().GetFullName())) {
						// If public and valid type add to list
						ScriptFieldType fieldType = Utils::s_ScriptFieldTypeMap[field.GetType().GetFullName()];

						ScriptField scriptField{
							.Name = field.GetName(),
							.Type = fieldType
						};

						fieldsVector.push_back(scriptField);
					} else {
						RE_CORE_WARN("Field '{0}' in class '{1}' has unsupported type '{2}' and will be ignored in the script editor", std::string(field.GetName()), className, std::string(field.GetType().GetFullName()));
					}
				}
			}

			fieldMap[className] = fieldsVector;
		}

		return fieldMap;
	}
}
