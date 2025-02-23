#include "Buffer.h"

#include <glad/glad.h>

namespace RealEngine {
	Buffer::Buffer(BufferType type, uint32_t size) 
		: m_Type(type) {
		CreateBuffer(nullptr, size);
	}

	Buffer::Buffer(BufferType type, void* data, uint32_t size) 
		: m_Type(type) {
		CreateBuffer(data, size);
	}

	Buffer::~Buffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void Buffer::Bind() const {
		glBindBuffer(m_Type, m_RendererID);
	}

	void Buffer::CreateBuffer(void* data, uint32_t size) {
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(m_Type, m_RendererID);
		glBufferData(m_Type, size, data, GL_STATIC_DRAW); // Customize draw type
	}
}
