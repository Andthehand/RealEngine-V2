#include "RealEngine.h"

#include <filesystem>

namespace RealEngine {
	class PannelFolderSelectEvent : public Event {
	public:
		PannelFolderSelectEvent(const std::filesystem::path& path)
			: m_Path(path) {}

		inline const std::filesystem::path& GetPath() const { return m_Path; }

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "PannelFolderSelectEvent: " << m_Path.string();
			return ss.str();
		}

		EVENT_CLASS_TYPE(PannelFolderSelect)
	private:
		const std::filesystem::path m_Path;
	};
}