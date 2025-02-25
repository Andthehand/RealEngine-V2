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

	void Buffer::Unbind() const {
		glBindBuffer(m_Type, 0);
	}

	void Buffer::CreateBuffer(void* data, uint32_t size) {
		RE_PROFILE_FUNCTION();

		glGenBuffers(1, &m_RendererID);
		Bind();
		glBufferData(m_Type, size, data, GL_STATIC_DRAW); // Customize draw type
	}

	VertexBuffer::VertexBuffer(uint32_t size)
		: Buffer(VertexBufferType, size) {}

	VertexBuffer::VertexBuffer(void* data, uint32_t size)
		: Buffer(VertexBufferType, data, size) {}

	IndexBuffer::IndexBuffer(uint32_t size)
		: Buffer(IndexBufferType, size) {}
	
	IndexBuffer::IndexBuffer(void* data, uint32_t size)
		: Buffer(IndexBufferType, data, size) {}
}
