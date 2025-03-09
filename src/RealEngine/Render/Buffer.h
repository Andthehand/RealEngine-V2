#pragma once
#include <cstdint>
#include <initializer_list>
#include <vector>

#define BUFFER_CLASS_TYPE(type)		type(uint32_t size) : Utils::Buffer(Utils::type, size) {}\
									type(const void* data, uint32_t size) : Utils::Buffer(Utils::type, data, size) {}\
									BUFFER_CLASS_CREATE(type)\
									BUFFER_CLASS_NAME(type)

#define BUFFER_CLASS_CREATE(type)	static Ref<type> Create(uint32_t size) { return CreateRef<type>(size); }\
									static Ref<type> Create(const void* data, uint32_t size) { return CreateRef<type>(data, size); }


#define BUFFER_CLASS_NAME(type)		virtual const char* GetName() const override { return #type; }

namespace RealEngine {
	namespace Utils {
		enum BufferType {
			VertexBuffer = GL_ARRAY_BUFFER,
			IndexBuffer = GL_ELEMENT_ARRAY_BUFFER,
			ShaderStorageBuffer = GL_SHADER_STORAGE_BUFFER,
			UniformBuffer = GL_UNIFORM_BUFFER
		};
		
		//This should never be used outside of the buffer class
		class Buffer {
		public:
			Buffer(BufferType type, uint32_t size);
			Buffer(BufferType type, const void* data, uint32_t size);
			~Buffer();

			virtual const char* GetName() const = 0;
			virtual std::string ToString() const { return std::string(GetName()) + " RenderId: " + std::to_string(m_RendererID); };

			void Bind() const;
			void Unbind() const;

			void SetData(void* data, const uint32_t size);

			BufferType GetType() const { return m_Type; }
		private:
			void CreateBuffer(const void* data, uint32_t size);
		protected:
			uint32_t m_RendererID;
			uint32_t m_Size;
			BufferType m_Type;
		};
	}

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

	class VertexBuffer : public Utils::Buffer {
	public:
		BUFFER_CLASS_TYPE(VertexBuffer)

		//This is used in the Vertex Array class to set the layout of the buffer
		void SetLayout(const BufferAttributes& attributes) { m_Attributes = attributes; }
		const BufferAttributes& GetLayout() const { return m_Attributes;  }
	private:
		BufferAttributes m_Attributes = {};
	};

	//This is just a wrapper around the buffer class for typdefing
	class IndexBuffer : public Utils::Buffer {
	public:
		IndexBuffer(uint32_t count);
		IndexBuffer(const uint32_t* data, uint32_t count);

		uint32_t GetCount() const { return m_Count; }

		BUFFER_CLASS_NAME(IndexBuffer)

		static Ref<IndexBuffer> Create(uint32_t size) { return CreateRef<IndexBuffer>(size); }
		static Ref<IndexBuffer> Create(const uint32_t* data, uint32_t size) { return CreateRef<IndexBuffer>(data, size); }
	private:
		const uint32_t m_Count;
	};

	class ShaderStorageBuffer : public Utils::Buffer {
	public:
		BUFFER_CLASS_TYPE(ShaderStorageBuffer)
	};

	// You must set the binging point in the shader does not support automatic binding
	class UniformBuffer : public Utils::Buffer {
	public:
		UniformBuffer(uint32_t size, uint32_t binding);
		UniformBuffer(const void* data, uint32_t size, uint32_t binding);

		void SetBinding(uint32_t binding);
		uint32_t GetBinding() const { return m_Binding; }

		BUFFER_CLASS_NAME(UniformBuffer)

		static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding) { return CreateRef<UniformBuffer>(size, binding); }
		static Ref<UniformBuffer> Create(const void* data, uint32_t size, uint32_t binding) { return CreateRef<UniformBuffer>(data, size, binding); }
	private:
		uint32_t m_Binding;
	};
}