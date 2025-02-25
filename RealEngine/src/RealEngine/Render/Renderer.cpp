#include "Renderer.h"

#include <glad/glad.h>

namespace RealEngine {
	void Renderer::Init() {
        RE_PROFILE_FUNCTION();

        RE_CORE_ASSERT(!m_Renderer, "Renderer is already initialized");
		m_Renderer = new Renderer();

        m_Shader = CreateScope<Shader>("assets/shaders/uber.shader");

        float vertices[] = {
            // positions          // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };


        Ref<IndexBuffer> ebo = CreateRef<IndexBuffer>(indices, (uint32_t)sizeof(indices));
        Ref<VertexBuffer> vbo = CreateRef<VertexBuffer>(vertices, (uint32_t)sizeof(vertices));
        vbo->SetLayout(BufferAttributes{
			{ DataType::Float3 },
			{ DataType::Float2 }
		});


        m_VAO = CreateScope<VertexArray>();
        m_VAO->SetVertexBuffer(vbo);
        m_VAO->SetIndexBuffer(ebo);

        m_Texture = CreateScope<Texture2D>("assets/textures/RGBA_Test.png");
	}

	void Renderer::Shutdown() {
        RE_PROFILE_FUNCTION();
        RE_CORE_ASSERT(m_Renderer, "Renderer is not initialized");

		delete m_Renderer;
	}

	void Renderer::Render() {
		RE_PROFILE_FUNCTION();

        m_Shader->Bind();
        m_Texture->Bind();
		m_VAO->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}