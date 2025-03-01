#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace RealEngine {
	class RenderCommands {
	public:
		static void Init() {
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glEnable(GL_DEPTH_TEST);

			const char* vendor = (char*)glGetString(GL_VENDOR);
			const char* renderer = (char*)glGetString(GL_RENDERER);
			const char* version = (char*)glGetString(GL_VERSION);
			const char* glslVersion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
			RE_CORE_INFO("OpenGL Info:");
			RE_CORE_INFO("    OpenGL Vendor: {0}", vendor);
			RE_CORE_INFO("    OpenGL Renderer: {0}", renderer);
			RE_CORE_INFO("    OpenGL Version: {0}", version);
			RE_CORE_INFO("    GLSL Version: {0}", glslVersion);
		}

		static void Clear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		static void SetClearColor(const glm::vec4& color) {
			glClearColor(color.r, color.g, color.b, color.a);
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			glViewport(x, y, width, height);
		}
	};
}