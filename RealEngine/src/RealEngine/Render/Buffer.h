#pragma once
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace RealEngine {
	class DataType {
	public:
		enum Type : uint8_t {
			Float = 1,
			Float2 = 2,
			Float3 = 3,

			Undefined
		};
	public:
		DataType() = delete;
		DataType(Type type) : m_Type(type) {}

		uint8_t GetTypeElementCount() { return m_Type; }

		uint8_t GetTypeSizeOf() { 
			switch (m_Type)
			{
				case DataType::Float:
				case DataType::Float2:
				case DataType::Float3:
					return sizeof(float);
				case RealEngine::DataType::Undefined:
					RE_CORE_ASSERT(false, "Undefined is your selected DataType?");
					return 0;
			}

			RE_CORE_ASSERT(false, "DataType not implmented yet!");
			return 0;
		}

		GLint GetGLType() const {
			switch (m_Type) {
				case DataType::Float:	
				case DataType::Float2:	
				case DataType::Float3:	
					return GL_FLOAT;
			}

			RE_CORE_ASSERT(false, "DataType not implmented yet!");
			return Undefined;
		}
	private:
		Type m_Type;
	};

	enum BufferType {
		VertexBufferType	= GL_ARRAY_BUFFER,
		IndexBufferType		= GL_ELEMENT_ARRAY_BUFFER
	};

	struct BufferAttribute {
		DataType Type;
		uint32_t InstanceDivisor = 0;
		uint8_t Size = 0;
		uint32_t Offset = 0;

		BufferAttribute() = delete;
		BufferAttribute(DataType type)
			: Type(type) {}
		BufferAttribute(DataType type, uint32_t instanceDivisor)
			: Type(type), InstanceDivisor(instanceDivisor) {}
	};

	struct BufferAttributes {
		BufferAttributes(std::initializer_list<BufferAttribute> vertexAttribs)
			: m_VertexAttribs(vertexAttribs) {
			uint32_t offset = 0;
			for (BufferAttribute& attrib : m_VertexAttribs) {
				attrib.Offset = offset;
				offset += attrib.Type.GetTypeElementCount() * attrib.Type.GetTypeSizeOf();
				attrib.Size = attrib.Type.GetTypeElementCount();
			}
			Stride = offset;
		}

		uint32_t Stride;
		std::vector<BufferAttribute> m_VertexAttribs;
	};

	class Buffer {
	public:
		Buffer(BufferType type, const uint32_t size);
		Buffer(BufferType type, void* data, const uint32_t size);
		~Buffer();

		void Bind() const;
		void Unbind() const;

		BufferType GetType() const { return m_Type; }
	private:
		void CreateBuffer(void* data, uint32_t size);
	protected:
		uint32_t m_RendererID;
		uint32_t m_Size;
		BufferType m_Type;
	};

	class VertexBuffer : public Buffer {
	public:
		VertexBuffer(const uint32_t size);
		VertexBuffer(void* data, const uint32_t size);

		void SetData(void* data, const uint32_t size);

		void SetLayout(const BufferAttributes& attributes) { m_Attributes = attributes; }
		const BufferAttributes& GetLayout() const { return m_Attributes;  }
	private:
		BufferAttributes m_Attributes = {};
	};

	//This is just a wrapper around the buffer class for typdefing
	class IndexBuffer : public Buffer {
	public:
		IndexBuffer(const uint32_t size);
		IndexBuffer(void* data, const uint32_t size);
	};
}