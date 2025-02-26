#include "Buffer.h"

#include <glad/glad.h>

namespace RealEngine {
	Buffer::Buffer(BufferType type, const uint32_t size) 
		: m_Type(type), m_Size(size) {
		CreateBuffer(nullptr, size);
	}

	Buffer::Buffer(BufferType type, void* data, const uint32_t size) 
		: m_Type(type), m_Size(size) {
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
		glBufferData(m_Type, size, data, GL_DYNAMIC_DRAW); // Customize draw type
	}

	VertexBuffer::VertexBuffer(const uint32_t size)
		: Buffer(VertexBufferType, size) {}

	VertexBuffer::VertexBuffer(void* data, const uint32_t size)
		: Buffer(VertexBufferType, data, size) {}

	void VertexBuffer::SetData(void* data, const uint32_t size) {
		RE_PROFILE_FUNCTION();
		RE_CORE_ASSERT(size <= m_Size, "Data size is greater than buffer size");

		Bind();
		glBufferSubData(m_Type, 0, size, data);
	}

	IndexBuffer::IndexBuffer(const uint32_t size)
		: Buffer(IndexBufferType, size) {}
	
	IndexBuffer::IndexBuffer(void* data, const uint32_t size)
		: Buffer(IndexBufferType, data, size) {}
}
