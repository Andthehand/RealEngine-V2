#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace RealEngine {
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {
	}

	void ImGuiLayer::OnAttach() {
		RE_PROFILE_FUNCTION();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		// Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		SetScale(Application::Get().GetWindow().GetScale());

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach() {
		RE_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}


	void ImGuiLayer::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowRescaledEvent>(RE_BIND_EVENT_FN(ImGuiLayer::OnWindowRescaled));
	}

	bool ImGuiLayer::OnWindowRescaled(WindowRescaledEvent& e) {
		SetScale(e.GetScale());

		return true;
	}

	void ImGuiLayer::SetScale(float scale) {
		RE_PROFILE_FUNCTION();

		ImGuiStyle& style = ImGui::GetStyle();
		style = ImGuiStyle();
		style.ScaleAllSizes(scale + SCALE_OFFSET);

		ImGuiIO& io = ImGui::GetIO();
		io.FontGlobalScale = scale + SCALE_OFFSET;
	}

	void ImGuiLayer::Begin() {
		RE_PROFILE_FUNCTION();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {
		RE_PROFILE_FUNCTION();
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		{
			RE_PROFILE_SCOPE("Updating viewports");
			// Update and Render additional Platform Windows
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}