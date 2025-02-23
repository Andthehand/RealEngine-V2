#pragma once 
#include "Texture.h"
#include "Buffer.h"

namespace RealEngine {
	class Renderer {
	public:
		static void Init();
		static void Shutdown();

		static Renderer* Get() { return m_Renderer; }

		void Render();
	private:
		static inline Renderer* m_Renderer = nullptr;

		static inline Scope<Texture2D> m_Texture;

		static inline uint32_t m_ShaderProgram = 0;
		static inline uint32_t m_VAO = 0;
		static inline Scope<VertexBuffer> m_VBO;
		static inline uint32_t m_EBO = 0;
	};
}