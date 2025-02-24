#pragma once
#include <cstdint>
#include <filesystem>
#include <string>

namespace RealEngine {
	enum ShaderTypes {
		Fragment,
		Vertex,

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

	private:
		void CompileShader(const std::vector<ShaderProcessing>& shaderProcessing);
		void ParseFile(const std::filesystem::path& file);
	private:
		uint32_t m_ShaderID;
	};
}