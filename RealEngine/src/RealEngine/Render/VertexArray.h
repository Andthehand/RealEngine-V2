#pragma once
#include "Buffer.h"

namespace RealEngine {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;
		void Unbind() const;

		void SetVertexBuffer(Ref<VertexBuffer> vertexBuffer);
		void SetIndexBuffer(Ref<IndexBuffer> indexBuffer);
	private:
		uint32_t m_RendererID;

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}