#pragma once 
#include "Texture.h"
#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"

#include "glm/glm.hpp"

namespace RealEngine {
	/**
	 * @class Renderer
	 * @brief High-level rendering interface for drawing and managing render state.
	 *
	 * Provides static methods to initialize and shutdown the renderer,
	 * draw simple primitives like quads, and access the singleton renderer instance.
	 */
	class Renderer {
	public:
		static void Init();
		static void Shutdown();

		/**
		 * @brief Draws a textured quad at the specified 3D position.
		 * @param position The position in world space where the quad will be drawn.
		 */
		static void DrawQuad(const glm::vec3& position);

		static void Flush();

		/**
		 * @brief Executes the render process. Typically called once per frame.
		 */
		static void Render();
	private:
		static inline Renderer* m_Renderer = nullptr;

		// The default texture used for rendering quads
		static inline Ref<Texture2D> m_Texture;
	};
}