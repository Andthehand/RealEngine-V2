#pragma once
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace RealEngine {
	enum DataType : uint8_t {
		Float	= 1,
		Float2	= 2,
		Float3	= 3,

		Undefined
	};

	enum BufferType {
		VertexBufferType	= GL_ARRAY_BUFFER,
		IndexBufferType		= GL_ELEMENT_ARRAY_BUFFER
	};

	struct BufferAttribute {
		DataType Type;
		uint32_t Size = 0;
		uint32_t Offset = 0;

		BufferAttribute() = delete;
		BufferAttribute(DataType type)
			: Type(type) {}

		GLint GetGLType() const {
			switch (Type) {
				case RealEngine::Float:		return GL_FLOAT;
				case RealEngine::Float2:	return GL_FLOAT;
				case RealEngine::Float3:	return GL_FLOAT;
			}

			RE_CORE_ASSERT(false, "DataType not implemented yet");
			return Undefined;
		}
	};

	struct BufferAttributes {
		BufferAttributes(std::initializer_list<BufferAttribute> vertexAttribs)
			: m_VertexAttribs(vertexAttribs) {
			uint32_t offset = 0;
			for (BufferAttribute& attrib : m_VertexAttribs) {
				attrib.Offset = offset;
				offset += attrib.Type * sizeof(float); // TODO: change from float to lookup
				attrib.Size = attrib.Type;
			}
			Stride = offset;
		}

		uint32_t Stride;
		std::vector<BufferAttribute> m_VertexAttribs;
	};

	class Buffer {
	public:
		Buffer(BufferType type, uint32_t size);
		Buffer(BufferType type, void* data, uint32_t size);
		~Buffer();

		void Bind() const;
		void Unbind() const;

		BufferType GetType() const { return m_Type; }
	private:
		void CreateBuffer(void* data, uint32_t size);
	private:
		uint32_t m_RendererID;
		BufferType m_Type;
	};

	class VertexBuffer : public Buffer {
	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(void* data, uint32_t size);

		void SetLayout(const BufferAttributes& attributes) { m_Attributes = attributes; }
		const BufferAttributes& GetLayout() const { return m_Attributes;  }
	private:
		BufferAttributes m_Attributes = {};
	};

	//This is just a wrapper around the buffer class for typdefing
	class IndexBuffer : public Buffer {
	public:
		IndexBuffer(uint32_t size);
		IndexBuffer(void* data, uint32_t size);
	};
}