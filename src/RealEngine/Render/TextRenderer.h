#pragma once

#include "RealEngine/Scene/Components.h"

#include "RealEngine/Render/RenderStats.h"
#include "RealEngine/Render/VertexArray.h"
#include "RealEngine/Render/Shader.h"
#include "RealEngine/Types/Font.h"

namespace RealEngine {
	class TextRenderer {
	public:
		TextRenderer(RenderStats* stats);
		~TextRenderer() = default;

		void RenderText(TransformComponent& transformComponent, const TextRendererComponent& textComponent);
		void FlushText(Ref<Font> font);
	private:
		void UpdateRenderStats();
	private:
		static constexpr uint32_t MAX_BATCH_LETTERS = 2000;

		struct GlyphData {
			glm::vec2 Position;
			glm::vec2 Size;

			glm::vec2 UV[4];
		};

		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;
		Ref<ShaderStorageBuffer> m_SSBO;

		Ref<Shader> m_TextShader;

		struct TextRenderData {
			glm::mat4 Transform;
			glm::vec4 Color;
			GlyphData Glyphs[MAX_BATCH_LETTERS];
		};
		TextRenderData m_RenderData;
		GlyphData* m_RenderDataHead = m_RenderData.Glyphs;

		RenderStats* m_Stats;
	};
}
