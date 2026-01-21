#include "ImGuiLayer.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include "OpenSansBold.h"
#include "OpenSansRegular.h"

namespace RealEngine {
	namespace Utils {
		void StyleColorsCustomDark() {
			ImGuiStyle& style = ImGui::GetStyle();
			ImVec4* c = style.Colors;

			auto RGBA = [](int r, int g, int b, int a = 255) -> ImVec4 {
				return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
			};

			// Base palette
			const ImVec4 colBg0 = RGBA(15, 15, 15, 240);
			const ImVec4 colBg1 = RGBA(22, 22, 22, 255);
			const ImVec4 colBg2 = RGBA(32, 32, 32, 255);
			const ImVec4 colBg3 = RGBA(42, 42, 42, 255);
			const ImVec4 colBg4 = RGBA(55, 55, 55, 255);
			const ImVec4 colOutline = RGBA(94, 94, 102, 128);
			const ImVec4 colAccent = RGBA(66, 149, 245, 255);     // Accent (slightly softer blue)
			const ImVec4 colAccentHi = RGBA(82, 173, 255, 255);
			const ImVec4 colWarn = RGBA(255, 198, 0, 255);
			const ImVec4 colError = RGBA(255, 109, 90, 255);

			// Text
			c[ImGuiCol_Text] = RGBA(255, 255, 255);
			c[ImGuiCol_TextDisabled] = RGBA(128, 128, 128);
			c[ImGuiCol_TextLink] = colAccent;
			c[ImGuiCol_TextSelectedBg] = ImVec4(colAccent.x, colAccent.y, colAccent.z, 0.35f);

			// Windowing
			c[ImGuiCol_WindowBg] = ImVec4(colBg0.x, colBg0.y, colBg0.z, 0.94f);
			c[ImGuiCol_ChildBg] = ImVec4(0, 0, 0, 0);
			c[ImGuiCol_PopupBg] = ImVec4(colBg0.x + 0.02f, colBg0.y + 0.02f, colBg0.z + 0.02f, 0.94f);

			// Borders / separators
			c[ImGuiCol_Border] = colOutline;
			c[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
			c[ImGuiCol_Separator] = c[ImGuiCol_Border];
			c[ImGuiCol_SeparatorHovered] = ImVec4(colAccent.x, colAccent.y, colAccent.z, 0.78f);
			c[ImGuiCol_SeparatorActive] = colAccent;

			// Frames (inputs, combo, etc.)
			c[ImGuiCol_FrameBg] = ImVec4(0.361f, 0.388f, 0.416f, 0.314f);
			c[ImGuiCol_FrameBgHovered] = ImVec4(0.361f, 0.388f, 0.416f, 0.4706f);
			c[ImGuiCol_FrameBgActive] = ImVec4(0.361f, 0.388f, 0.416f, 0.6275f);

			// Title bars
			c[ImGuiCol_TitleBg] = RGBA(10, 10, 10);
			c[ImGuiCol_TitleBgActive] = RGBA(10, 10, 10);
			c[ImGuiCol_TitleBgCollapsed] = RGBA(0, 0, 0, 130);

			// Menu / navigation overlays
			c[ImGuiCol_MenuBarBg] = RGBA(36, 36, 36);
			c[ImGuiCol_NavWindowingHighlight] = RGBA(255, 255, 255, 178);
			c[ImGuiCol_NavWindowingDimBg] = RGBA(204, 204, 204, 51);
			c[ImGuiCol_NavCursor] = colAccentHi;
			c[ImGuiCol_ModalWindowDimBg] = RGBA(204, 204, 204, 89);

			// Scrollbars
			c[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
			c[ImGuiCol_ScrollbarGrab] = RGBA(79, 79, 79);
			c[ImGuiCol_ScrollbarGrabHovered] = RGBA(105, 105, 105);
			c[ImGuiCol_ScrollbarGrabActive] = RGBA(130, 130, 130);

			// Check / slider / resize grips
			c[ImGuiCol_CheckMark] = colAccent;
			c[ImGuiCol_SliderGrab] = ImVec4(colAccent.x * 0.92f, colAccent.y * 0.92f, colAccent.z * 0.92f, 1.0f);
			c[ImGuiCol_SliderGrabActive] = colAccentHi;
			c[ImGuiCol_ResizeGrip] = ImVec4(colAccent.x, colAccent.y, colAccent.z, 0.20f);
			c[ImGuiCol_ResizeGripHovered] = ImVec4(colAccent.x, colAccent.y, colAccent.z, 0.67f);
			c[ImGuiCol_ResizeGripActive] = ImVec4(colAccent.x, colAccent.y, colAccent.z, 0.95f);
			c[ImGuiCol_InputTextCursor] = c[ImGuiCol_Text];

			// Headers / buttons / tabs
			const ImVec4 header = RGBA(60, 60, 60);
			const ImVec4 headerHovered = RGBA(77, 77, 77, 200);
			const ImVec4 headerActive = RGBA(77, 77, 77, 150);

			c[ImGuiCol_Header] = header;
			c[ImGuiCol_HeaderHovered] = headerHovered;
			c[ImGuiCol_HeaderActive] = headerActive;

			c[ImGuiCol_Button] = c[ImGuiCol_Header];
			c[ImGuiCol_ButtonHovered] = c[ImGuiCol_HeaderHovered];
			c[ImGuiCol_ButtonActive] = c[ImGuiCol_HeaderActive];

			// Tabs (derive from headers + title)
			c[ImGuiCol_Tab] = ImLerp(c[ImGuiCol_Header], c[ImGuiCol_TitleBgActive], 0.80f);
			c[ImGuiCol_TabHovered] = c[ImGuiCol_HeaderHovered];
			c[ImGuiCol_TabSelected] = ImLerp(c[ImGuiCol_HeaderActive], c[ImGuiCol_TitleBgActive], 0.60f);
			c[ImGuiCol_TabDimmed] = ImLerp(c[ImGuiCol_Tab], c[ImGuiCol_TitleBg], 0.80f);
			c[ImGuiCol_TabDimmedSelected] = ImLerp(c[ImGuiCol_TabSelected], c[ImGuiCol_TitleBg], 0.40f);
			c[ImGuiCol_TabSelectedOverline] = ImVec4(0.103f, 0.351f, 0.918f, 1.000f);

			// Docking
			c[ImGuiCol_DockingPreview] = ImVec4(c[ImGuiCol_HeaderActive].x, c[ImGuiCol_HeaderActive].y, c[ImGuiCol_HeaderActive].z, 0.70f);
			c[ImGuiCol_DockingEmptyBg] = RGBA(51, 51, 51);

			// Tables
			c[ImGuiCol_TableHeaderBg] = RGBA(49, 49, 51);
			c[ImGuiCol_TableBorderStrong] = RGBA(79, 79, 89);
			c[ImGuiCol_TableBorderLight] = RGBA(59, 59, 64);
			c[ImGuiCol_TableRowBg] = ImVec4(0, 0, 0, 0);
			c[ImGuiCol_TableRowBgAlt] = ImVec4(1, 1, 1, 0.06f);

			// Plots
			c[ImGuiCol_PlotLines] = RGBA(156, 156, 156);
			c[ImGuiCol_PlotLinesHovered] = colError;
			c[ImGuiCol_PlotHistogram] = colWarn;
			c[ImGuiCol_PlotHistogramHovered] = RGBA(255, 153, 0);

			// Trees / misc
			c[ImGuiCol_TreeLines] = c[ImGuiCol_Border];
			c[ImGuiCol_DragDropTarget] = RGBA(255, 255, 0, 230);

			// Rounding & layout tweaks
			style.FrameRounding = 5.0f;
			style.GrabRounding = 2.0f;
			style.GrabMinSize = 12.0f;
			style.ScrollbarRounding = 9.0f;
			style.WindowRounding = 4.0f;
			style.PopupRounding = 4.0f;
			style.TabRounding = 4.0f;
			style.TabBarOverlineSize = 3.0f;

			// Spacing (subtle adjustments for balance)
			style.WindowPadding = ImVec2(10, 10);
			style.FramePadding = ImVec2(6, 4);
			style.ItemSpacing = ImVec2(8, 6);
			style.ItemInnerSpacing = ImVec2(6, 4);
			style.IndentSpacing = 18.0f;
			style.ScrollbarSize = 14.0f;
		}
	}

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {
	}

	void ImGuiLayer::OnAttach() {
		RE_PROFILE_FUNCTION();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		//ImGui::StyleColorsDark();
		Utils::StyleColorsCustomDark();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		// Enable Multi-Viewport / Platform Windows

		SetScale();

		ImFontConfig fontConfig = ImFontConfig();
		fontConfig.FontDataOwnedByAtlas = false; // So we don't try to free the static memory
		io.Fonts->AddFontFromMemoryTTF((void*)Utils::OpenSans_Bold, sizeof(Utils::OpenSans_Bold), 0.0f, &fontConfig);
		io.FontDefault = io.Fonts->AddFontFromMemoryTTF((void*)Utils::OpenSans_Regular, sizeof(Utils::OpenSans_Regular), 0.0f, &fontConfig);

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

	void ImGuiLayer::SetScale() {
		RE_PROFILE_FUNCTION();

		ImGuiStyle& style = ImGui::GetStyle();
		float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
		style.ScaleAllSizes(main_scale);
		style.FontScaleDpi = main_scale;

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigDpiScaleFonts = true;
		io.ConfigDpiScaleViewports = true;
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