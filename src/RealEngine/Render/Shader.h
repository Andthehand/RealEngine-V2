#pragma once
#include <cstdint>
#include <filesystem>
#include <string>

namespace RealEngine {
	/**
	 * @enum ShaderTypes
	 * @brief Enumerates supported shader types.
	 */
	enum ShaderTypes {
		Fragment,
		Vertex,
		Compute,

		Unknown
	};

	/**
	 * @struct ShaderProcessing
	 * @brief Holds shader source code along with its type for processing.
	 */
	struct ShaderProcessing {
		std::string ShaderCode;
		const ShaderTypes ShaderType;
	};

	/**
	 * @class Shader
	 * @brief Encapsulates an OpenGL shader program.
	 *
	 * Provides functionality to load, compile, and bind shaders.
	 */
	class Shader {
	public:
		/**
		 * @brief Constructs a shader by loading from a file.
		 * @param file The filesystem path to the shader file.
		 */
		Shader(const std::filesystem::path& file);
		/**
		 * @brief Constructs a shader from vertex and fragment shader source code strings.
		 * @param vertexShaderSource Source code for the vertex shader.
		 * @param fragmentShaderSource Source code for the fragment shader.
		 */
		Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
		~Shader();

		void Bind() const;

		void SetUniformint(const std::string& name, int value);

		void SetUniformFloat(const std::string& name, float value);
		void SetUniformVec2(const std::string& name, const glm::vec2& value);
		void SetUniformVec3(const std::string& name, const glm::vec3& value);
		void SetUniformVec4(const std::string& name, const glm::vec4& value);

		/**
		 * @brief Creates a reference-counted shader from a file path.
		 * @param file Path to the shader file.
		 * @return Ref-counted pointer to the created Shader.
		 */
		static Ref<Shader> Create(const std::filesystem::path& file) { return CreateRef<Shader>(file); }
		/**
		 * @brief Creates a reference-counted shader from vertex and fragment source code strings.
		 * @param vertexShaderSource Source code for the vertex shader.
		 * @param fragmentShaderSource Source code for the fragment shader.
		 * @return Ref-counted pointer to the created Shader.
		 */
		static Ref<Shader> Create(const char* vertexShaderSource, const char* fragmentShaderSource) { return CreateRef<Shader>(vertexShaderSource, fragmentShaderSource); }
	private:
		/**
		 * @brief Compiles the shader from processed source code blocks.
		 * @param shaderProcessing Vector of ShaderProcessing structs containing code and type.
		 */
		void CompileShader(const std::vector<ShaderProcessing>& shaderProcessing);

		/**
		 * @brief Parses a shader file and extracts shader code blocks by type.
		 * @param file Filesystem path to the shader file.
		 */
		void ParseFile(const std::filesystem::path& file);
	private:
		uint32_t m_ShaderID;
	};
}