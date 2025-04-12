#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "VertexArray.h"

namespace RealEngine {
	class RenderCommands {
	public:
		static void Init();

		static void Clear();
		static void SetClearColor(const glm::vec4& color);

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetWireframe(bool enabled);

		static void SetFaceCulling(bool enabled);

		static void DrawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount = 0);
		//TODO: If you pass in 0 for count, it will draw the entire buffer by querying the buffer size from the vertexArray
		static void DrawArrays(Ref<VertexArray> vertexArray, uint32_t count);

		static void DrawMutliIndexedIndirect(Ref<VertexArray> vertexArray, uint32_t commandCount);
	};
}