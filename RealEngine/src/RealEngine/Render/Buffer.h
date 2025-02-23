#pragma once
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace RealEngine {
	enum DataType : uint8_t {
		Float	= 1,
		Float2	= 2,
		Float3	= 3
	};

	struct BufferAttribute {
		DataType type;
		uint32_t stride;
	};

	struct BufferAttributes {
		BufferAttributes(std::initializer_list<BufferAttribute> vertexAttribs)
			: m_VertexAttribs(vertexAttribs) {
			uint32_t stride = 0;
			for (BufferAttribute& attrib : m_VertexAttribs) {
				attrib.stride = stride;
				stride += attrib.type;
			}
		}

		std::vector<BufferAttribute> m_VertexAttribs;
	};

	class VertexBuffer {
	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(void* data, uint32_t size);
		~VertexBuffer();

		void Bind() const;
	private:
		void CreateBuffer(void* data, uint32_t size);
	private:
		uint32_t m_RendererID;
	};
}