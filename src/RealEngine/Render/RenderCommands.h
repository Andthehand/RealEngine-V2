#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "VertexArray.h"

namespace RealEngine {
	/**
	 * @class RenderCommands
	 * @brief Encapsulates OpenGL rendering commands and state setup.
	 *
	 * Provides static methods to initialize OpenGL state,
	 * set viewport and clear colors, and issue draw calls.
	 */
	class RenderCommands {
	public:
		/**
		 * @brief Initializes the rendering state, enables depth testing,
		 * and logs OpenGL version information.
		 */
		static void Init() {
			RE_PROFILE_FUNCTION();
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_DEPTH_TEST);

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

		/**
		 * @brief Clears the framebuffer's color and depth buffers.
		 */
		static void Clear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		/**
		 * @brief Sets the color used when clearing the framebuffer.
		 * @param color RGBA clear color.
		 */
		static void SetClearColor(const glm::vec4& color) {
			glClearColor(color.r, color.g, color.b, color.a);
		}

		/**
		 * @brief Sets the OpenGL viewport dimensions.
		 * @param x X coordinate of the lower-left corner of the viewport.
		 * @param y Y coordinate of the lower-left corner of the viewport.
		 * @param width Width of the viewport in pixels.
		 * @param height Height of the viewport in pixels.
		 */
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			glViewport(x, y, width, height);
		}

		/**
		 * @brief Enables or disables wireframe mode for rendering.
		 * @param enabled True to enable wireframe rendering, false for fill mode.
		 */
		static void SetWireframe(bool enabled) {
			glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
		}

		/**
		 * @brief Draws primitives from the currently bound vertex array using indexed drawing.
		 * @param vertexArray Reference to the vertex array to draw.
		 * @param indexCount Number of indices to draw. If 0, draws all indices in the index buffer.
		 */
		static void DrawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount = 0) {
			RE_PROFILE_FUNCTION();
			vertexArray->Bind();

			uint32_t count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}

		/**
		 * @brief Draws primitives from the currently bound vertex array using array drawing.
		 * @param vertexArray Reference to the vertex array to draw.
		 * @param count Number of vertices to draw.
		 *
		 * @todo Support default value of 0 to draw entire vertex buffer by querying vertex count.
		 */
		static void DrawArrays(Ref<VertexArray> vertexArray, uint32_t count) {
			RE_PROFILE_FUNCTION();
			vertexArray->Bind();

			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	};
}