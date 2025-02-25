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
		RE_PROFILE_FUNCTION();

		m_VertexBuffer = vertexBuffer;
		
		Bind();
		m_VertexBuffer->Bind();
		const BufferAttributes& layout = m_VertexBuffer->GetLayout();
		const std::vector<BufferAttribute>& attribs = layout.m_VertexAttribs;
		for (uint8_t i = 0; i < attribs.size(); i++) {
			const BufferAttribute& attrib = attribs[i];
            glVertexAttribPointer(i, attrib.Size, attrib.Type.GetGLType(), GL_FALSE, layout.Stride, (void*)(uintptr_t)attrib.Offset);
			glEnableVertexAttribArray(i);
		}
	}

	void VertexArray::SetIndexBuffer(Ref<IndexBuffer> indexBuffer) {
		RE_PROFILE_FUNCTION();

		m_IndexBuffer = indexBuffer;
		Bind();
		m_IndexBuffer->Bind();
	}
}