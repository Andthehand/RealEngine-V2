#include "RealEngine/Core/Dialogs.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "RealEngine/Core/Application.h"

namespace RealEngine {
	namespace Utils {
		OPENFILENAMEA CreateOFN(char* outBuffer, DWORD bufferSize, const char* filter, DWORD flags) {
			OPENFILENAMEA ofn;
			CHAR currentDir[256] = { 0 };

			ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
			ofn.lStructSize = sizeof(OPENFILENAMEA);
			ofn.hwndOwner = glfwGetWin32Window(
				(GLFWwindow*)Application::Get().GetWindow().GetNativeWindow()
			);
			ofn.lpstrFile = outBuffer;
			ofn.nMaxFile = bufferSize;

			if (GetCurrentDirectoryA(256, currentDir))
				ofn.lpstrInitialDir = currentDir;

			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = flags;

			return ofn;
		}
	}

	std::filesystem::path FileDialogs::OpenFile(const char* filter) {
		RE_PROFILE_FUNCTION();

		char fileBuffer[260] = { 0 };

		OPENFILENAMEA ofn = Utils::CreateOFN(
			fileBuffer,
			sizeof(fileBuffer),
			filter,
			OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR
		);

		if (GetOpenFileNameA(&ofn) == TRUE)
			return std::filesystem::path(fileBuffer);

		return {};
	}

	std::filesystem::path FileDialogs::SaveFile(const char* filter) {
		RE_PROFILE_FUNCTION();

		char fileBuffer[260] = { 0 };

		OPENFILENAMEA ofn = Utils::CreateOFN(
			fileBuffer,
			sizeof(fileBuffer),
			filter,
			OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR
		);

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = "*";

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();
	}
}
