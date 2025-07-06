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
		static void Init();

		/**
		 * @brief Clears the framebuffer's color and depth buffers.
		 */
		static void Clear();
		/**
		 * @brief Sets the color used when clearing the framebuffer.
		 * @param color RGBA clear color.
		 */
		static void SetClearColor(const glm::vec4& color);

		/**
		 * @brief Sets the OpenGL viewport dimensions.
		 * @param x X coordinate of the lower-left corner of the viewport.
		 * @param y Y coordinate of the lower-left corner of the viewport.
		 * @param width Width of the viewport in pixels.
		 * @param height Height of the viewport in pixels.
		 */
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		/**
		 * @brief Enables or disables wireframe mode for rendering.
		 * @param enabled True to enable wireframe rendering, false for fill mode.
		 */
		static void SetWireframe(bool enabled);

		/**
		* @brief Enables or disables face culling (GL_CULL_FACE).
		* @param enabled If true, enable back-face culling. Otherwise, disable it.
		*/
		static void SetFaceCulling(bool enabled);

		/**
		 * @brief Draws primitives from the currently bound vertex array using indexed drawing.
		 * @param vertexArray Reference to the vertex array to draw.
		 * @param indexCount Number of indices to draw. If 0, draws all indices in the index buffer.
		 */
		static void DrawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount = 0);
		//TODO: If you pass in 0 for count, it will draw the entire buffer by querying the buffer size from the vertexArray
		static void DrawArrays(Ref<VertexArray> vertexArray, uint32_t count);

		static void DrawMutliIndexedIndirect(Ref<VertexArray> vertexArray, uint32_t commandCount);
	};
}