#pragma once

#include "RealEngine/Scene/Components.h"

#include "RealEngine/Render/VertexArray.h"
#include "RealEngine/Render/Shader.h"
#include "RealEngine/Types/Font.h"

namespace RealEngine {
	// Forward declare because of circular dependency
	class Scene;

	class SceneRenderer {
	public:
		SceneRenderer(Scene* scene);
		SceneRenderer() = delete;

		~SceneRenderer() = default;

		void OnRender(const glm::mat4& cameraProjection);
	private:
		void AddSprite(TransformComponent& transform, const SpriteRendererComponent& sprite);

		void Flush2D();
		void FlushText();
	private:
		Scene* m_Scene;

		struct GlyphData {
			glm::vec2 Position;
			glm::vec2 Size;

			glm::vec2 UV[4];
		};

		struct TextData {
			Ref<VertexArray> VAO;
			Ref<VertexBuffer> VBO;
			Ref<ShaderStorageBuffer> SSBO;

			Ref<Shader> TextShader;
			Ref<Font> Font;

			static constexpr uint32_t MaxBatchLetters = 2000;

			struct TextRenderData {
				glm::mat4 Transform;
				glm::vec4 Color;
				GlyphData Glyphs[MaxBatchLetters];
			};

			TextRenderData RenderData;
			GlyphData* RenderDataHead = RenderData.Glyphs;
		};

		struct SpriteRenderData {
			glm::vec3 Position;
			glm::vec4 Color;
			uint32_t TexIndex;
		};

		struct Render2DData {
			Ref<VertexArray> VAO;
			Ref<VertexBuffer> VBO;

			Ref<Shader> SpriteShader;
			Ref<Texture2D> WhiteTexture;

			static constexpr uint32_t MaxQuadCount = 250;
			static constexpr uint32_t MaxVerticesCount = MaxQuadCount * 4;
			static constexpr uint32_t MaxIndicesCount = MaxQuadCount * 6;
			static constexpr uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

			std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
			uint32_t TextureSlotIndex = 1; // 0 = white texture

			uint32_t QuadCount = 0;
			SpriteRenderData RenderData[MaxVerticesCount];
			SpriteRenderData* RenderDataHead = RenderData;
		};

		Ref<UniformBuffer> m_CameraBuffer;
		Render2DData m_Render2DData;
		TextData m_TextData;
	};
}
