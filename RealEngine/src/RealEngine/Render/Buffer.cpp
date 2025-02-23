#include "Buffer.h"

#include <glad/glad.h>

namespace RealEngine {
	VertexBuffer::VertexBuffer(uint32_t size) {
		CreateBuffer(nullptr, size);
	}

	VertexBuffer::VertexBuffer(void* data, uint32_t size) {
		CreateBuffer(data, size);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::CreateBuffer(void* data, uint32_t size) {
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // Customize draw type
	}
}
