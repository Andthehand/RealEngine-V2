#include "RenderCommands.h"

namespace RealEngine {
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam) {
		RE_PROFILE_FUNCTION();

		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH:			RE_CORE_CRITICAL("GLFW Error: {}", message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:			RE_CORE_ERROR("GLFW Error: {}", message); return;
			case GL_DEBUG_SEVERITY_LOW:				RE_CORE_WARN("GLFW Error: {}", message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION:	RE_CORE_TRACE("GLFW Error: {}", message); return;
		}

		RE_CORE_ASSERT(false, "Unknown severity level!");
	}

	void RenderCommands::Init() {
		RE_PROFILE_FUNCTION();
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef RE_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_FALSE);
#endif

		const char* vendor = (char*)glGetString(GL_VENDOR);
		const char* renderer = (char*)glGetString(GL_RENDERER);
		const char* version = (char*)glGetString(GL_VERSION);
		const char* glslVersion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
		RE_CORE_INFO("OpenGL Info:");
		RE_CORE_INFO("    OpenGL Vendor: {0}", vendor);
		RE_CORE_INFO("    OpenGL Renderer: {0}", renderer);
		RE_CORE_INFO("    OpenGL Version: {0}", version);
		RE_CORE_INFO("    GLSL Version: {0}", glslVersion);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
	}

	void RenderCommands::Clear() {
		RE_PROFILE_FUNCTION();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommands::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RenderCommands::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	void RenderCommands::SetWireframe(bool enabled) {
		glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
	}

	void RenderCommands::SetFaceCulling(bool enabled) {
		if (enabled) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else {
			glDisable(GL_CULL_FACE);
		}
	}

	void RenderCommands::DrawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount) {
		RE_PROFILE_FUNCTION();
		vertexArray->Bind();

		uint32_t count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void RenderCommands::DrawArrays(Ref<VertexArray> vertexArray, uint32_t count) {
		RE_PROFILE_FUNCTION();
		vertexArray->Bind();

		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void RenderCommands::DrawMutliIndexedIndirect(Ref<VertexArray> vertexArray, uint32_t commandCount) {
		RE_PROFILE_FUNCTION();
		vertexArray->Bind();

		glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, commandCount, 0);
	}
}