#include "Renderer.h"

#include <glad/glad.h>

namespace RealEngine {
	void Renderer::Init() {
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
        glGenVertexArrays(1, &m_VAO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

        m_VBO = CreateScope<Buffer>(VertexBuffer, vertices, (uint32_t)sizeof(vertices));
        glBindVertexArray(m_VAO);

        m_EBO = CreateScope<Buffer>(ElementBuffer, indices, (uint32_t)sizeof(indices));

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);

        m_Texture = CreateScope<Texture2D>("assets/textures/RGBA_Test.png");
	}

	void Renderer::Shutdown() {
		RE_CORE_ASSERT(m_Renderer, "Renderer is not initialized");

        glDeleteVertexArrays(1, &m_VAO);

		delete m_Renderer;
	}

	void Renderer::Render() {
        m_Shader->Bind();
        m_Texture->Bind();
        glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}