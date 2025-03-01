#pragma once

namespace RealEngine{
	enum class FramebufferTextureFormat {
		None = 0,

		// Color
		RGBA8 = GL_RGBA8,
		RED_INTEGER = GL_R8,

		// Depth/stencil
		DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,

		// Defaults
		Depth = DEPTH24_STENCIL8
	};

	struct FramebufferTextureSpecification {
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering/wrap
	};

	struct FramebufferAttachmentSpecification {
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	struct FramebufferSpecification {
		FramebufferAttachmentSpecification Attachments;

		uint32_t Width = 0, Height = 0;
	};

	class Framebuffer {
	public:
		Framebuffer(const FramebufferSpecification& specs);
		~Framebuffer();

		void Bind();
		void Unbind();
		void Resize(uint32_t width, uint32_t height);
		
		uint32_t GetAttachmentRendererID(uint32_t index = 0) const { return m_Attachments[index]; }
	private:
		void Invalidate();
	private:
		uint32_t m_FramebufferID = 0;

		FramebufferSpecification m_Specification;

		std::vector<uint32_t> m_Attachments;
	};
}