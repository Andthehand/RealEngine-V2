#include "Shader.h"
#include <algorithm>

namespace RealEngine {
	/// @cond NO_DOXYGEN
	namespace Utils {
		struct ValidShaderName {
			const char* SymbolicName;
			ShaderTypes ShaderType;
		};

		bool ichar_equals(char a, char b)
		{
			return std::tolower(static_cast<unsigned char>(a)) ==
				std::tolower(static_cast<unsigned char>(b));
		}

		bool iequals(const std::string_view a, const std::string_view b)
		{
			return a.size() == b.size() &&
				std::equal(a.begin(), a.end(), b.begin(), ichar_equals);
		}

		inline ShaderTypes CheckShaderTypeString(const std::string_view view) {
			if (iequals(view, "fragment"))	return Fragment;
			if (iequals(view, "vertex"))	return Vertex;
			if (iequals(view, "compute"))	return Compute;

			RE_CORE_ASSERT(false, "Unknown Shader Type when parsing!");
			return Unknown;
		}

		inline const std::string_view ShaderTypeToString(const ShaderTypes shaderType) {
			switch (shaderType) {
				case Fragment: return "Fragment";
				case Vertex: return "Vertex";
				case Compute: return "Compute";
			}

			RE_CORE_ASSERT(false, "ShaderType not implemented yet");
			return "Unknown";
		}

		inline GLint ShaderTypeToGLType(const ShaderTypes shaderType) {
			switch (shaderType) {
				case Fragment: return GL_FRAGMENT_SHADER;
				case Vertex: return GL_VERTEX_SHADER;
				case Compute: return GL_COMPUTE_SHADER;
			}

			RE_CORE_ASSERT(false, "ShaderType not implemented yet");
			return Unknown;
		}
	}
	/// @endcond

	Shader::Shader(const std::filesystem::path& file) {
		ParseFile(file);
	}

	Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource) {
		std::vector<ShaderProcessing> shaderProcessing = {
			{ vertexShaderSource, Vertex },
			{ fragmentShaderSource, Fragment }
		};
		CompileShader(shaderProcessing);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderID);
	}

	void Shader::Bind() const {
		glUseProgram(m_ShaderID);
	}

	void Shader::SetUniformint(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
	}

	void Shader::SetUniformFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value);
	}

	void Shader::SetUniformVec2(const std::string& name, const glm::vec2& value) {
		glUniform2f(glGetUniformLocation(m_ShaderID, name.c_str()), value.x, value.y);
	}

	void Shader::SetUniformVec3(const std::string& name, const glm::vec3& value) {
		glUniform3f(glGetUniformLocation(m_ShaderID, name.c_str()), value.x, value.y, value.z);
	}

	void Shader::SetUniformVec4(const std::string& name, const glm::vec4& value) {
		glUniform4f(glGetUniformLocation(m_ShaderID, name.c_str()), value.x, value.y, value.z, value.w);
	}

    void Shader::CompileShader(const std::vector<ShaderProcessing>& shaderProcessing) {
		RE_PROFILE_FUNCTION();
		std::vector<uint32_t> shaderIDs;
        for (const ShaderProcessing& shaderCode : shaderProcessing) {
            shaderIDs.push_back(glCreateShader(Utils::ShaderTypeToGLType(shaderCode.ShaderType)));

            const char* shaderSource = shaderCode.ShaderCode.c_str();
            glShaderSource(shaderIDs.back(), 1, &shaderSource, NULL);
            glCompileShader(shaderIDs.back());

            //Check for errors
            int success;
            glGetShaderiv(shaderIDs.back(), GL_COMPILE_STATUS, &success);
            if (!success) {
                int maxLength = 0;
                glGetShaderiv(shaderIDs.back(), GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<char> infoLog(maxLength);
                glGetShaderInfoLog(shaderIDs.back(), maxLength, &maxLength, &infoLog[0]);

                glGetShaderInfoLog(shaderIDs.back(), 512, NULL, &infoLog[0]);
                RE_CORE_ERROR("{0} shader compilation failed: {1}", Utils::ShaderTypeToString(shaderCode.ShaderType), infoLog.data());
            }
        }

        // shader Program
        m_ShaderID = glCreateProgram();
        for (const uint32_t id : shaderIDs) {
            glAttachShader(m_ShaderID, id);
        }
        glLinkProgram(m_ShaderID);

        //Check for errors
        int success;
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
        for (const uint32_t id : shaderIDs) {
            glDeleteShader(id);
        }
    }

	void Shader::ParseFile(const std::filesystem::path& file) {
		RE_PROFILE_FUNCTION();
		RE_CORE_ASSERT(std::filesystem::exists(file))

		std::ifstream stream(file);
		if (!stream.is_open()) {
			RE_CORE_ERROR("Failed to open file: {0}", file.string());
			return;
		}

		// Read in file to string
		std::string fileString((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		std::vector<ShaderProcessing> shaderProcessing;
		size_t offset = fileString.find("#type");
		RE_CORE_ASSERT(offset != std::string::npos, "No shader code found in file {0}", file);
		while (offset != std::string::npos) {
			offset += 5; // Skip #type
			offset = fileString.find_first_not_of(" \t\r\n", offset);

			size_t endOfShaderType = fileString.find_first_of("\r\n", offset);
			std::string_view shaderTypeString = std::string_view(fileString.data() + offset, endOfShaderType - offset);
			ShaderTypes shaderType = Utils::CheckShaderTypeString(shaderTypeString);

			offset = fileString.find("#type", offset); // Get position of next shader code
			shaderProcessing.push_back({ fileString.substr(endOfShaderType, offset - endOfShaderType), shaderType});
		}

		CompileShader(shaderProcessing);
	}
}
