#include "EditorLayer.h"

#include <imgui.h>

namespace RealEngine {
	EditorLayer::EditorLayer()
		: Layer("Editor") {}

	void EditorLayer::OnAttach() {
		RE_PROFILE_FUNCTION();

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
		RE_PROFILE_FUNCTION();

		m_Framebuffer->Bind();
		RenderCommands::Clear();

		Renderer::Get()->DrawQuad({ 0.0f, 0.0f, 0.0f });
		Renderer::Get()->Render();

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGui() {
		RE_PROFILE_FUNCTION();

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

		if(ImGui::BeginMenuBar()) {
			if(ImGui::BeginMenu("File")) {
				if(ImGui::MenuItem("Exit"))
					Application::Get().Stop();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View")) {
				ImGui::MenuItem("Properties", NULL, &m_PropertiesPanel.IsVisible);
				ImGui::MenuItem("FileExplorer", NULL, &m_FileExplorerPanel.IsVisible);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window")) {
				if (ImGui::MenuItem("Vsync", NULL, Application::Get().GetWindow().GetVsync())) {
					Application::Get().GetWindow().SetVSync(!Application::Get().GetWindow().GetVsync());
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		if (m_PropertiesPanel.IsVisible)
			m_PropertiesPanel.OnImGui();
		if (m_FileExplorerPanel.IsVisible)
			m_FileExplorerPanel.OnImGui();

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

		//ImGui::ShowDemoWindow();
	}

	void EditorLayer::OnEvent(Event& event) {
		RE_PROFILE_FUNCTION();

		m_PropertiesPanel.OnEvent(event);
	}
}
