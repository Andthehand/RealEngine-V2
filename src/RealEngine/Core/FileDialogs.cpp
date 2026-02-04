#include "FileDialogs.h"

namespace RealEngine {
	std::filesystem::path FileDialogs::OpenFile(std::initializer_list<nfdfilteritem_t> filter) {
		NFD::Guard nfdGuard;
		NFD::UniquePath outPath;

		nfdresult_t result = NFD::OpenDialog(outPath, filter.begin(), filter.size());
		if (result == NFD_OKAY) {
			return std::filesystem::path(outPath.get());
		}
		else if (result == NFD_ERROR) {
			RE_CORE_ERROR("OpenFile Dialog Error: {0}", NFD::GetError());
		}

		// User pressed cancel
		return "";
	}

	std::filesystem::path FileDialogs::SaveFile(std::initializer_list<nfdfilteritem_t> filter) {
		NFD::Guard nfdGuard;
		NFD::UniquePath outPath;

		nfdresult_t result = NFD::SaveDialog(outPath, filter.begin(), filter.size());
		if (result == NFD_OKAY) {
			return std::filesystem::path(outPath.get());
		}
		else if (result == NFD_ERROR) {
			RE_CORE_ERROR("SaveFile Dialog Error: {0}", NFD::GetError());
		}

		// User pressed cancel
		return "";
	}

	std::filesystem::path FileDialogs::PickFolder() {
		NFD::Guard nfdGuard;
		NFD::UniquePath outPath;

		nfdresult_t result = NFD::PickFolder(outPath);
		if (result == NFD_OKAY) {
			return std::filesystem::path(outPath.get());
		}
		else if (result == NFD_ERROR) {
			RE_CORE_ERROR("SaveFile Dialog Error: {0}", NFD::GetError());
		}

		// User pressed cancel
		return "";
	}
}
