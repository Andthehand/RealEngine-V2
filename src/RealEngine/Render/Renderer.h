#pragma once 
#include "Texture.h"
#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"

#include "glm/glm.hpp"

namespace RealEngine {
	class Renderer {
	public:
		static void Init();
		static void Shutdown();

		static void DrawQuad(const glm::vec3& position);

		static Renderer* Get() { return m_Renderer; }

		void Render();
	private:
		static inline Renderer* m_Renderer = nullptr;

		static inline Ref<Texture2D> m_Texture;
	};
}