#pragma once
#include <filesystem>
#include <initializer_list>

#include <nfd.hpp>

namespace RealEngine {
	class FileDialogs {
	public:
		static std::filesystem::path OpenFile(std::initializer_list<nfdfilteritem_t> filter = {{ .name = "All Files", .spec = "*" }});
		static std::filesystem::path SaveFile(std::initializer_list<nfdfilteritem_t> filter = {{ .name = "All Files", .spec = "*" }});
		static std::filesystem::path PickFolder();
	};
}