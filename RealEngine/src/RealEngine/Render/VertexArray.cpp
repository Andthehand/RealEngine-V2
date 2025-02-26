#include "VertexArray.h"

#include <glad/glad.h>

namespace RealEngine {
	VertexArray::VertexArray() {
		RE_PROFILE_FUNCTION();

		glGenVertexArrays(1, &m_RendererID);
	}
	
	VertexArray::~VertexArray() {
		RE_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void VertexArray::SetVertexBuffer(Ref<VertexBuffer> vertexBuffer) {
		std::vector<Ref<VertexBuffer>> buffers = { vertexBuffer };
		SetVertexBuffers(buffers);
	}

	void VertexArray::SetVertexBuffers(std::vector<Ref<VertexBuffer>> vertexBuffers) {
		RE_PROFILE_FUNCTION();
		m_VertexBuffer = vertexBuffers;
		
		Bind();
		uint8_t index = 0; // Since there are multiple VBO we need to keep track of the what the gloabal index is
		for (const Ref<VertexBuffer> vertexBuffer : vertexBuffers) {
			vertexBuffer->Bind();

			const BufferAttributes& layout = vertexBuffer->GetLayout();
			const std::vector<BufferAttribute>& attribs = layout.m_VertexAttribs;
			for (uint8_t i = 0; i < attribs.size(); i++) {
				const BufferAttribute& attrib = attribs[i];
				glVertexAttribPointer(index, attrib.Size, attrib.Type.GetGLType(), GL_FALSE, layout.Stride, (void*)(uintptr_t)attrib.Offset);
				glVertexAttribDivisor(index, attrib.InstanceDivisor);
				glEnableVertexAttribArray(index);
				index++;
			}
		}
	}

	void VertexArray::SetIndexBuffer(Ref<IndexBuffer> indexBuffer) {
		RE_PROFILE_FUNCTION();

		m_IndexBuffer = indexBuffer;
		Bind();
		m_IndexBuffer->Bind();
	}
}