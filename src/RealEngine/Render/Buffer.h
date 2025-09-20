#pragma once
#include <cstdint>
#include <initializer_list>
#include <vector>

/**
 * @def BUFFER_CLASS_TYPE(type)
 * @brief Declares constructor overloads, static creation methods, and a name override for a buffer type.
 */
#define BUFFER_CLASS_TYPE(type)		type(uint32_t size) : Utils::Buffer(Utils::type, size) {}\
									type(const void* data, uint32_t size) : Utils::Buffer(Utils::type, data, size) {}\
									BUFFER_CLASS_CREATE(type)\
									BUFFER_CLASS_NAME(type)

 /**
  * @def BUFFER_CLASS_CREATE(type)
  * @brief Declares static factory creation methods for the buffer type.
  */
#define BUFFER_CLASS_CREATE(type)	static Ref<type> Create(uint32_t size) { return CreateRef<type>(size); }\
									static Ref<type> Create(const void* data, uint32_t size) { return CreateRef<type>(data, size); }


  /**
   * @def BUFFER_CLASS_NAME(type)
   * @brief Implements the GetName() method returning the buffer's type name as a string.
   */
#define BUFFER_CLASS_NAME(type)		virtual const char* GetName() const override { return #type; }

namespace RealEngine {
	namespace Utils {
		/**
		 * @brief Enum representing OpenGL buffer binding targets.
		 */
		enum BufferType {
			VertexBuffer = GL_ARRAY_BUFFER,
			IndexBuffer = GL_ELEMENT_ARRAY_BUFFER,
			ShaderStorageBuffer = GL_SHADER_STORAGE_BUFFER,
			UniformBuffer = GL_UNIFORM_BUFFER,
			CommandBuffer = GL_DRAW_INDIRECT_BUFFER,
		};
		
		/**
		 * @brief Low-level OpenGL buffer abstraction. Not intended for direct use.
		 */
		class Buffer {
		public:
			Buffer(BufferType type, uint32_t size);
			Buffer(BufferType type, const void* data, uint32_t size);
			~Buffer();

			virtual const char* GetName() const = 0;
			virtual std::string ToString() const { return std::string(GetName()) + " RenderId: " + std::to_string(m_RendererID); };

			void Bind() const;
			void Unbind() const;

			void SetData(const void* data, uint32_t size, uint32_t offset = 0);

			BufferType GetType() const { return m_Type; }
			uint32_t GetSize() const { return m_Size; }
		private:
			void CreateBuffer(const void* data, uint32_t size);
		protected:
			uint32_t m_RendererID;
			uint32_t m_Size;
			BufferType m_Type;
		};
	}

	/**
	 * @brief Wrapper for abstracting data types and layouts in vertex buffers.
	 */
	class DataType {
	public:
		enum Type : uint8_t {
			Float,
			Float2,
			Float3,
			Float4,

			Uint,
			Uint2,
			Uint3,
			Uint4,

			Int,
			Int2,
			Int3,
			Int4,

			Undefined
		};
	public:
		DataType() = delete;
		DataType(Type type) : m_Type(type) {}

		Type GetType() const { return m_Type; }

		/// Number of components (e.g., Float3 → 3)
		uint8_t GetTypeElementCount() { 
			switch (m_Type) {
				case RealEngine::DataType::Float:		return 1;
				case RealEngine::DataType::Float2:		return 2;
				case RealEngine::DataType::Float3:		return 3;
				case RealEngine::DataType::Float4:		return 4;
				case RealEngine::DataType::Uint:		return 1;
				case RealEngine::DataType::Uint2:		return 2;
				case RealEngine::DataType::Uint3:		return 3;
				case RealEngine::DataType::Uint4:		return 4;
				case RealEngine::DataType::Int:			return 1;
				case RealEngine::DataType::Int2:		return 2;
				case RealEngine::DataType::Int3:		return 3;
				case RealEngine::DataType::Int4:		return 4;
				case RealEngine::DataType::Undefined:
					RE_CORE_ASSERT(false, "Undefined is your selected DataType?");
					return 0;
			}

			RE_CORE_ASSERT(false, "DataType not implmented yet!");
			return 0;
		}

		/// Size in bytes of the base type (e.g., Float4 → sizeof(float))
		uint8_t GetTypeSizeOf() { 
			switch (m_Type)
			{
				case DataType::Float:
				case DataType::Float2:
				case DataType::Float3:
				case DataType::Float4:
					return sizeof(float);
				case DataType::Uint:
				case DataType::Uint2:
				case DataType::Uint3:
				case DataType::Uint4:
					return sizeof(uint32_t);
				case DataType::Int:
				case DataType::Int2:
				case DataType::Int3:
				case DataType::Int4:
					return sizeof(int32_t);
				case RealEngine::DataType::Undefined:
					RE_CORE_ASSERT(false, "Undefined is your selected DataType?");
					return 0;
			}

			RE_CORE_ASSERT(false, "DataType not implmented yet!");
			return 0;
		}

		/// OpenGL enum (GL_FLOAT, GL_INT, etc.)
		GLint GetGLType() const {
			switch (m_Type) {
				case DataType::Float:	
				case DataType::Float2:	
				case DataType::Float3:	
				case DataType::Float4:
					return GL_FLOAT;
				case DataType::Uint:
				case DataType::Uint2:
				case DataType::Uint3:
				case DataType::Uint4:
					return GL_UNSIGNED_INT;
				case DataType::Int:
				case DataType::Int2:
				case DataType::Int3:
				case DataType::Int4:
					return GL_INT;
				case RealEngine::DataType::Undefined:
					RE_CORE_ASSERT(false, "Undefined is your selected DataType?");
					return 0;
			}

			RE_CORE_ASSERT(false, "DataType not implmented yet!");
			return Undefined;
		}
	private:
		Type m_Type;
	};
	
	/**
	 * @brief Single attribute used in a vertex layout.
	 */
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

	/**
	 * @brief Aggregates multiple buffer attributes and computes overall stride.
	 */
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

	/**
	 * @brief Vertex buffer with a definable layout.
	 */
	class VertexBuffer : public Utils::Buffer {
	public:
		BUFFER_CLASS_TYPE(VertexBuffer)

		//This is used in the Vertex Array class to set the layout of the buffer
		void SetLayout(const BufferAttributes& attributes) { m_Attributes = attributes; }
		const BufferAttributes& GetLayout() const { return m_Attributes;  }
	private:
		BufferAttributes m_Attributes = {};
	};

	/**
	 * @brief Specialization of buffer for index/element use.
	 */
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

	/**
	 * @brief Wrapper around OpenGL shader storage buffer object (SSBO).
	 */
	class ShaderStorageBuffer : public Utils::Buffer {
	public:
		ShaderStorageBuffer(uint32_t size, uint32_t binding);
		ShaderStorageBuffer(const void* data, uint32_t size, uint32_t binding);

		void SetBinding(uint32_t binding);
		uint32_t GetBinding() const { return m_Binding; }

		BUFFER_CLASS_NAME(ShaderStorageBuffer)

		static Ref<ShaderStorageBuffer> Create(uint32_t size, uint32_t binding) { return CreateRef<ShaderStorageBuffer>(size, binding); }
		static Ref<ShaderStorageBuffer> Create(const void* data, uint32_t size, uint32_t binding) { return CreateRef<ShaderStorageBuffer>(data, size, binding); }
	private:
		uint32_t m_Binding;
	};

	/**
	 * @brief Wrapper for OpenGL UBOs.
	 * @note User must manually bind the layout index in GLSL.
	 */
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

	/**
	 * @brief Buffer for issuing indirect draw commands.
	 */
	class CommandBuffer : public Utils::Buffer {
	public:
		BUFFER_CLASS_TYPE(CommandBuffer)
	};
}
