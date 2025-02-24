#pragma once
#include <cstdint>
#include <filesystem>

namespace RealEngine {
	class Shader {
	public:
		Shader(const std::filesystem::path& file);
		Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
		~Shader();

		void Bind() const;

	private:
		void CompileShader(const char* vertexShaderSource, const char* fragmentShaderSource);
		void ParseFile(const std::filesystem::path& file);
	private:
		uint32_t m_ShaderID;
	};
}