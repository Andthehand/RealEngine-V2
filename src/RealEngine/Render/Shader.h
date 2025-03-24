#pragma once
#include <cstdint>
#include <filesystem>
#include <string>

namespace RealEngine {
	enum ShaderTypes {
		Fragment,
		Vertex,
		Compute,

		Unknown
	};

	struct ShaderProcessing {
		std::string ShaderCode;
		const ShaderTypes ShaderType;
	};

	class Shader {
	public:
		Shader(const std::filesystem::path& file);
		Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
		~Shader();

		void Bind() const;

		void SetUniformint(const std::string& name, int value);

		void SetUniformFloat(const std::string& name, float value);
		void SetUniformVec2(const std::string& name, const glm::vec2& value);
		void SetUniformVec3(const std::string& name, const glm::vec3& value);
		void SetUniformVec4(const std::string& name, const glm::vec4& value);

		static Ref<Shader> Create(const std::filesystem::path& file) { return CreateRef<Shader>(file); }
		static Ref<Shader> Create(const char* vertexShaderSource, const char* fragmentShaderSource) { return CreateRef<Shader>(vertexShaderSource, fragmentShaderSource); }
	private:
		void CompileShader(const std::vector<ShaderProcessing>& shaderProcessing);
		void ParseFile(const std::filesystem::path& file);
	private:
		uint32_t m_ShaderID;
	};
}