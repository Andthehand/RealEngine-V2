#include "Shader.h"

namespace RealEngine {
	Shader::Shader(const std::filesystem::path& file) {
		
	}

	Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource) {
		CompileShader(vertexShaderSource, fragmentShaderSource);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderID);
	}

	void Shader::Bind() const {
		glUseProgram(m_ShaderID);
	}

	void Shader::CompileShader(const char* vertexShaderSource, const char* fragmentShaderSource) {
		int success;
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexShaderSource, NULL);
        glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			int maxLength = 0;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertex, maxLength, &maxLength, &infoLog[0]);

			glGetShaderInfoLog(vertex, 512, NULL, &infoLog[0]);
			RE_CORE_ERROR("Vertex shader compilation failed: {0}", infoLog.data());
		}

        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			int maxLength = 0;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(fragment, maxLength, &maxLength, &infoLog[0]);

			glGetShaderInfoLog(fragment, 512, NULL, &infoLog[0]);
			RE_CORE_ERROR("Fragment shader compilation failed: {0}", infoLog.data());
		}

        // shader Program
		m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertex);
        glAttachShader(m_ShaderID, fragment);
        glLinkProgram(m_ShaderID);
		glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
		if (!success) {
			int maxLength = 0;
			glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_ShaderID, maxLength, &maxLength, &infoLog[0]);
			RE_CORE_ERROR("Shader program linking failed: {0}", infoLog.data());

			glDeleteProgram(m_ShaderID);
		}

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
	}

	void Shader::ParseFile(const std::filesystem::path& file) {
	
	}
}