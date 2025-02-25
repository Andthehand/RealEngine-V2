#pragma once
#include "Buffer.h"

namespace RealEngine {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;

		void SetVertexBuffer(Ref<VertexBuffer> vertexBuffer);
	private:
		uint32_t m_RendererID;

		Ref<VertexBuffer> m_VertexBuffer;
	};
}