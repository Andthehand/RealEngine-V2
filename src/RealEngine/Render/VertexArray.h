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
		void SetVertexBuffers(std::vector<Ref<VertexBuffer>> vertexBuffers);
		void SetIndexBuffer(Ref<IndexBuffer> indexBuffer);
	private:
		uint32_t m_RendererID;

		std::vector<Ref<VertexBuffer>> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}