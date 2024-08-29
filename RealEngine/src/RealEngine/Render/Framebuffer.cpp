#include "Framebuffer.h"

namespace RealEngine {
	Framebuffer::Framebuffer(const FramebufferSpecification& specs)
		: m_Specification(specs) {
		RE_PROFILE_FUNCTION();

		m_Attachments.resize(m_Specification.Attachments.Attachments.size());

		Invalidate();
	}

	Framebuffer::~Framebuffer() {
		RE_PROFILE_FUNCTION();

		glDeleteFramebuffers(1, &m_FramebufferID);
		glDeleteTextures((GLsizei)m_Attachments.size(), m_Attachments.data());
	}

	void Framebuffer::Bind() {
		RE_PROFILE_FUNCTION();

		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void Framebuffer::Unbind() {
		RE_PROFILE_FUNCTION();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Resize(uint32_t width, uint32_t height) {
		RE_PROFILE_FUNCTION();

		m_Specification.Width = width;
		m_Specification.Height = height;
		Invalidate();
	}

	void Framebuffer::Invalidate() {
		RE_PROFILE_FUNCTION();

		if (m_FramebufferID) {
			glDeleteFramebuffers(1, &m_FramebufferID);
			glDeleteTextures((GLsizei)m_Attachments.size(), m_Attachments.data());
		}

		glCreateFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

		for (uint32_t i = 0; i < m_Attachments.size(); i++) {
			auto& attachment = m_Specification.Attachments.Attachments[i];

			glCreateTextures(GL_TEXTURE_2D, 1, &m_Attachments[i]);
			glBindTexture(GL_TEXTURE_2D, m_Attachments[i]);

			switch (attachment.TextureFormat) {
				case FramebufferTextureFormat::RGBA8:
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					break;
				case FramebufferTextureFormat::RED_INTEGER:
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, nullptr);
					break;
				case FramebufferTextureFormat::DEPTH24_STENCIL8:
					glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
					break;
				default:
					RE_CORE_ASSERT(false, "Unknown texture format");
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			if (attachment.TextureFormat != FramebufferTextureFormat::DEPTH24_STENCIL8) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Attachments[i], 0);
			}
			else {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_Attachments[i], 0);
			}

			RE_CORE_ASSERT(m_Attachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((GLsizei)m_Attachments.size(), buffers);

			RE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
		
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}