#pragma once

#include "RealEngine/Scene/Components.h"

#include "RealEngine/Render/RenderStats.h"
#include "RealEngine/Render/VertexArray.h"
#include "RealEngine/Render/Shader.h"

namespace RealEngine {
	class Renderer2D {
	public:
		Renderer2D(RenderStats* stats);
		~Renderer2D() = default;

		void DrawSprite(TransformComponent& transformComponent, const SpriteRendererComponent& spriteComponent);
		void Flush2D();
	private:
		void UpdateRenderStats();
	private:
		static constexpr uint32_t MAX_QUAD_COUNT = 250;
		static constexpr uint32_t MAX_VERTICES_COUNT = MAX_QUAD_COUNT * 4;
		static constexpr uint32_t MAX_INDICES_COUNT = MAX_QUAD_COUNT * 6;
		static constexpr uint32_t MAX_TEXTURE_SLOTS = 32; // TODO: RenderCaps

		struct SpriteRenderData {
			glm::vec3 Position;
			glm::vec4 Color;
			uint32_t TexIndex;
		};

		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;

		Ref<Shader> m_SpriteShader;
		Ref<Texture2D> m_WhiteTexture;

		std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> m_TextureSlots;
		uint32_t m_TextureSlotIndex = 1; // 0 = white texture

		uint32_t m_QuadCount = 0;
		SpriteRenderData m_RenderData[MAX_VERTICES_COUNT];
		SpriteRenderData* m_RenderDataHead = m_RenderData;

		RenderStats* m_Stats;
	};
}