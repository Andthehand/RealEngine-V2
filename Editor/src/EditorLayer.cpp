#include "EditorLayer.h"

#include <imgui.h>

namespace RealEngine {
	EditorLayer::EditorLayer()
		: Layer("Editor") {}

	void EditorLayer::OnAttach() {
		Application::Get().GetWindow().SetVSync(true);
		RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

		FramebufferSpecification spec;
		spec.Width = 1280;
		spec.Height = 720;
		spec.Attachments = { FramebufferTextureFormat::RGBA8 };

		m_Framebuffer = CreateRef<Framebuffer>(spec);
	}

	void EditorLayer::OnDetach() {
	}

	void EditorLayer::OnUpdate() {
		m_Framebuffer->Bind();
		RenderCommands::Clear();

		Renderer::Get()->Render();

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGui() {
		static bool s_DockspaceOpen = true;
		static ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking 
			| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize 
			| ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &s_DockspaceOpen, window_flags);

		ImGui::PopStyleVar(3);

		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Exit"))
					Application::Get().Stop();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();

		//ImGui Viewport Window/Panel
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();

		ImVec2 viewpoerPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewpoerPanelSize.x, viewpoerPanelSize.y };

		uint64_t textureID = m_Framebuffer->GetAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();


		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void EditorLayer::OnEvent(Event& event) {
	}
}
