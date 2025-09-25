#pragma once

namespace RealEngine{
	/**
	 * @enum FramebufferTextureFormat
	 * @brief Specifies the format of textures attached to a framebuffer.
	 */
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

	/**
	 * @struct FramebufferTextureSpecification
	 * @brief Describes a single texture attachment's format for a framebuffer.
	 */
	struct FramebufferTextureSpecification {
		/**
		 * @param format The texture format to use for this attachment.
		 */
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}
		FramebufferTextureSpecification() = default;

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering/wrap
	};

	/**
	 * @struct FramebufferAttachmentSpecification
	 * @brief Specifies a list of framebuffer texture attachments.
	 */
	struct FramebufferAttachmentSpecification {
		/**
		 * @param attachments Initializer list of texture specifications.
		 */
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}
		FramebufferAttachmentSpecification() = default;

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	/**
	 * @struct FramebufferSpecification
	 * @brief Configuration specification for creating a framebuffer.
	 */
	struct FramebufferSpecification {
		FramebufferAttachmentSpecification Attachments;

		uint32_t Width = 0, Height = 0;
	};

	/**
	 * @class Framebuffer
	 * @brief Represents an OpenGL framebuffer object with multiple texture attachments.
	 *
	 * Responsible for managing framebuffer creation, binding, resizing, and deletion.
	 */
	class Framebuffer {
	public:
		/**
		 * @brief Creates a framebuffer with the given specification.
		 * @param specs The specification describing attachments, size, etc.
		 */
		Framebuffer(const FramebufferSpecification& specs);
		~Framebuffer();

		void Bind();
		void Unbind();
		void Resize(uint32_t width, uint32_t height);

		/**
		 * @brief Returns the framebuffer's creation specification.
		 * @return Const reference to the specification (dimensions and attachment formats).
		 *
		 * Use this to query current size or attachment layout. Modifying the returned specification
		 * will NOT automatically recreate GPU resources—call Resize (for size changes) or provide
		 * a new Framebuffer instance if attachment formats change.
		 */
		const FramebufferSpecification& GetSpecification() { return m_Specification; }

		/**
		 * @brief Gets the renderer ID of a texture attachment.
		 * @param index Index of the attachment (default 0).
		 * @return OpenGL texture ID of the attachment.
		 */
		uint32_t GetAttachmentRendererID(uint32_t index = 0) const { return m_Attachments[index]; }
	private:
		/**
		 * @brief (Re)creates the framebuffer and its attachments based on the current specification.
		 *
		 * Deletes previous OpenGL objects if they exist, then allocates and attaches textures
		 * for all specified formats. Called on construction and resize.
		 */
		void Invalidate();
	private:
		uint32_t m_FramebufferID = 0;

		FramebufferSpecification m_Specification;

		std::vector<uint32_t> m_Attachments;
	};
}