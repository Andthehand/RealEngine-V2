#pragma once
#include "Buffer.h"

namespace RealEngine {
	/**
	 * @class VertexArray
	 * @brief Encapsulates an OpenGL Vertex Array Object (VAO) managing vertex and index buffers.
	 *
	 * Supports binding/unbinding, setting multiple vertex buffers, and an index buffer.
	 */
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		/**
		 * @brief Sets a single vertex buffer and configures its layout attributes.
		 * @param vertexBuffer Reference-counted pointer to a VertexBuffer.
		 */
		void SetVertexBuffer(Ref<VertexBuffer> vertexBuffer);
		/**
		 * @brief Sets multiple vertex buffers and configures their layouts.
		 * @param vertexBuffers Vector of reference-counted VertexBuffer pointers.
		 */
		void SetVertexBuffers(std::vector<Ref<VertexBuffer>> vertexBuffers);
		/**
		 * @brief Sets the index buffer used for indexed drawing.
		 * @param indexBuffer Reference-counted pointer to an IndexBuffer.
		 */
		void SetIndexBuffer(Ref<IndexBuffer> indexBuffer);

		/**
		 * @brief Creates a new VertexArray object wrapped in a Ref pointer.
		 * @return Reference-counted pointer to the new VertexArray.
		 */
		static Ref<VertexArray> Create() { return CreateRef<VertexArray>(); }

		const Ref<VertexBuffer> GetVertexBuffer(uint8_t index = 0) const { return m_VertexBuffer.at(index); }
		const Ref<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;

		std::vector<Ref<VertexBuffer>> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}