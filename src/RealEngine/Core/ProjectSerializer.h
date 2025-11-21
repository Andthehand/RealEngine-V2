#pragma once
#include "Project.h"

namespace RealEngine {
	class ProjectSerializer {
	public:
		ProjectSerializer() = delete;

		static bool Serialize(Ref<Project> project, const std::filesystem::path& filepath);
		static bool Deserialize(Ref<Project> project, const std::filesystem::path& filepath);
	private:
		Ref<Project> m_Project;
	};
}
