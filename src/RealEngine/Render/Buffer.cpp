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

			glCreateBuffers(1, &m_RendererID);
			glNamedBufferData(m_RendererID, size, data, GL_DYNAMIC_DRAW); // TODO: Customize draw type
		}

		void Buffer::SetData(const void* data, uint32_t size, uint32_t offset) {
			RE_PROFILE_FUNCTION();
			RE_CORE_ASSERT(size <= m_Size, "Data size is greater than buffer size");

			glNamedBufferSubData(m_RendererID, offset, size, data);
		}
	}

	IndexBuffer::IndexBuffer(uint32_t count)
		: Buffer(Utils::BufferType::IndexBuffer, count * sizeof(uint32_t)), m_Count(count) {
	}

	IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
		: Buffer(Utils::BufferType::IndexBuffer, (void*)data, count * sizeof(uint32_t)), m_Count(count) {
	}

	ShaderStorageBuffer::ShaderStorageBuffer(uint32_t size, uint32_t binding)
		: Buffer(Utils::BufferType::ShaderStorageBuffer, size) {
		SetBinding(binding);
	}

	ShaderStorageBuffer::ShaderStorageBuffer(const void* data, uint32_t size, uint32_t binding)
		: Buffer(Utils::BufferType::ShaderStorageBuffer, data, size) {
		SetBinding(binding);
	}

	void ShaderStorageBuffer::SetBinding(uint32_t binding) {
		m_Binding = binding;
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, m_RendererID);
	}

	UniformBuffer::UniformBuffer(uint32_t size, uint32_t binding) 
		: Buffer(Utils::BufferType::UniformBuffer, size) {
		SetBinding(binding);
	}

	UniformBuffer::UniformBuffer(const void* data, uint32_t size, uint32_t binding)
		: Buffer(Utils::BufferType::UniformBuffer, data, size) {
		SetBinding(binding);
	}

	void UniformBuffer::SetBinding(uint32_t binding) {
		m_Binding = binding;
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}
}
