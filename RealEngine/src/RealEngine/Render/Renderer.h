#pragma once 
#include "Texture.h"
#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"

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

		static inline Scope<Shader> m_Shader;
		static inline Scope<VertexArray> m_VAO;
	};
}