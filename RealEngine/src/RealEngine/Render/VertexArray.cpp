#include "VertexArray.h"

#include <glad/glad.h>

namespace RealEngine {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_RendererID);
	}
	
	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::SetVertexBuffer(Ref<VertexBuffer> vertexBuffer) {
		m_VertexBuffer = vertexBuffer;
		
		Bind();
		const BufferAttributes& layout = m_VertexBuffer->GetLayout();
		const std::vector<BufferAttribute>& attribs = layout.m_VertexAttribs;
		for (uint8_t i = 0; i < attribs.size(); i++) {
			const BufferAttribute& attrib = attribs[i];
            glVertexAttribPointer(i, attrib.Size, attrib.GetGLType(), GL_FALSE, layout.Stride, (void*)(uintptr_t)attrib.Offset);
			glEnableVertexAttribArray(i);
		}
	}
}