#include "Renderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "RealEngine/Resources/TextureManager.h"

namespace RealEngine {
    struct QuadData {
        glm::vec3 Vertices;
        glm::vec2 TextureCords;
    };

    struct RenderData {
        Ref<VertexArray> VAO;
        Ref<VertexBuffer> VBO;
        Ref<Shader> QuadShader;

        static constexpr uint32_t MaxQuadCount = 100;
        static constexpr uint32_t MaxVerticesCount = MaxQuadCount * 4;
        static constexpr uint32_t MaxIndicesCount = MaxQuadCount * 6;
        uint32_t Indices[MaxIndicesCount];

		uint32_t QuadCount = 0;
        QuadData RenderData[MaxVerticesCount];
		QuadData* RenderDataHead = RenderData;

        glm::vec4 QuadVertexPositions[4];
    };

	static RenderData s_RenderData;

	void Renderer::Init() {
        RE_PROFILE_FUNCTION();

        RE_CORE_ASSERT(!m_Renderer, "Renderer is already initialized");
		m_Renderer = new Renderer();

        for (uint32_t i = 0; i < s_RenderData.MaxIndicesCount; i += 6) {
			s_RenderData.Indices[i + 0] = i + 0;
			s_RenderData.Indices[i + 1] = i + 1;
			s_RenderData.Indices[i + 2] = i + 2;

			s_RenderData.Indices[i + 3] = i + 2;
			s_RenderData.Indices[i + 4] = i + 3;
			s_RenderData.Indices[i + 5] = i + 0;
        }

		s_RenderData.VAO = CreateScope<VertexArray>();
        Ref<IndexBuffer> ebo = CreateRef<IndexBuffer>(s_RenderData.Indices, (uint32_t)sizeof(s_RenderData.Indices));
        s_RenderData.VBO = CreateRef<VertexBuffer>((uint32_t)sizeof(s_RenderData.RenderData));
        s_RenderData.VBO->SetLayout(BufferAttributes{
			{ DataType::Float3 },
			{ DataType::Float2 }
		});

        s_RenderData.VAO = CreateScope<VertexArray>();
        s_RenderData.VAO->SetVertexBuffer(s_RenderData.VBO);
        s_RenderData.VAO->SetIndexBuffer(ebo);

        s_RenderData.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_RenderData.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
        s_RenderData.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
        s_RenderData.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

        s_RenderData.QuadShader = CreateScope<Shader>("assets/shaders/uber.shader");
        m_Texture = CreateRef<Texture2D>("assets/textures/RGBA_Test.png");
	}

	void Renderer::Shutdown() {
        RE_PROFILE_FUNCTION();
        RE_CORE_ASSERT(m_Renderer, "Renderer is not initialized");

		delete m_Renderer;
	}

    void Renderer::DrawQuad(const glm::vec3& position) {
		RE_PROFILE_FUNCTION();
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

        constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

        if (s_RenderData.RenderDataHead >= s_RenderData.RenderData) {
            s_RenderData.RenderDataHead = s_RenderData.RenderData;
        }

		for (uint32_t i = 0; i < 4; i++) {
			s_RenderData.RenderDataHead->Vertices = transform * s_RenderData.QuadVertexPositions[i];
			s_RenderData.RenderDataHead->TextureCords = textureCoords[i];
            s_RenderData.RenderDataHead++;
		}

		s_RenderData.QuadCount++;
    }

	void Renderer::Render() {
		RE_PROFILE_FUNCTION();

        s_RenderData.QuadShader->Bind();
        m_Texture->Bind();
        s_RenderData.VAO->Bind();
		s_RenderData.VBO->SetData(s_RenderData.RenderData, s_RenderData.QuadCount * 4 * (uint32_t)sizeof(QuadData));
        glDrawElements(GL_TRIANGLES, s_RenderData.QuadCount * 6, GL_UNSIGNED_INT, 0);

		s_RenderData.QuadCount = 0;
		s_RenderData.RenderDataHead = s_RenderData.RenderData;
	}
}