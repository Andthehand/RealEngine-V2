#include "Buffer.h"

#include <glad/glad.h>

namespace RealEngine {
	namespace Utils {
		Buffer::Buffer(BufferType Type, const BufferCreateInfo& specs)
			: m_Type(Type), m_Size(specs.Size) {
			CreateBuffer(specs.Data, m_Size, specs.Usage);
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

		void Buffer::CreateBuffer(const void* data, uint32_t size, BufferUsage usage) {
			RE_PROFILE_FUNCTION();

			glCreateBuffers(1, &m_RendererID);
			glNamedBufferData(m_RendererID, size, data, (GLenum)usage);
		}

		void Buffer::SetData(const void* data, uint32_t size, uint32_t offset) {
			RE_PROFILE_FUNCTION();
			RE_CORE_ASSERT(size <= m_Size, "Data size is greater than buffer size");

			glNamedBufferSubData(m_RendererID, offset, size, data);
		}
	}

	IndexBuffer::IndexBuffer(uint32_t count)
		: Buffer(Utils::BufferType::IndexBuffer, BufferCreateInfo{ 
													.Size = (uint32_t)(count * sizeof(uint32_t)) 
												}), m_Count(count) { }

	IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
		: Buffer(Utils::BufferType::IndexBuffer, BufferCreateInfo{ 
													.Size = (uint32_t)(count * sizeof(uint32_t)), 
													.Data = (void*)data 
												}), m_Count(count) { }

	ShaderStorageBuffer::ShaderStorageBuffer(const BufferCreateInfo& specs, uint32_t binding)
		: Buffer(Utils::BufferType::ShaderStorageBuffer, specs) {
		SetBinding(binding);
	}

	void ShaderStorageBuffer::SetBinding(uint32_t binding) {
		m_Binding = binding;
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, m_RendererID);
	}

	UniformBuffer::UniformBuffer(const BufferCreateInfo& specs, uint32_t binding) 
		: Buffer(Utils::BufferType::UniformBuffer, specs){
		SetBinding(binding);

	}

	void UniformBuffer::SetBinding(uint32_t binding) {
		m_Binding = binding;
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}
}
