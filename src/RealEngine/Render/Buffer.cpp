#include "Buffer.h"

#include <glad/glad.h>

namespace RealEngine {
	namespace Utils {
		Buffer::Buffer(BufferType type, uint32_t size)
			: m_Type(type), m_Size(size) {
			CreateBuffer(nullptr, size);
		}

		Buffer::Buffer(BufferType type, const void* data, uint32_t size)
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

		void Buffer::CreateBuffer(const void* data, uint32_t size) {
			RE_PROFILE_FUNCTION();

			glGenBuffers(1, &m_RendererID);
			Bind();
			glBufferData(m_Type, size, data, GL_DYNAMIC_DRAW); // Customize draw type
		}

		void Buffer::SetData(void* data, const uint32_t size) {
			RE_PROFILE_FUNCTION();
			RE_CORE_ASSERT(size <= m_Size, "Data size is greater than buffer size");

			Bind();
			glBufferSubData(m_Type, 0, size, data);
		}
	}

	IndexBuffer::IndexBuffer(uint32_t count)
		: Buffer(Utils::BufferType::IndexBuffer, count * sizeof(uint32_t)), m_Count(count) {
	}

	IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
		: Buffer(Utils::BufferType::IndexBuffer, (void*)data, count * sizeof(uint32_t)), m_Count(count) {
	}
}
