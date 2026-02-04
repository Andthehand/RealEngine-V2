#include "MessageDialog.h"

namespace RealEngine {
	namespace Utils {
		NMB::Result ShowDialog(const char* title, const char* message, NMB::Icon type) {
			return NMB::show(title, message, type);
		}
	}

	NMB::Result MessageDialog::InfoDialog(const char* title, const char* message) {
		return Utils::ShowDialog(title, message, NMB::Icon::ICON_INFO);
	}

	NMB::Result MessageDialog::WarnDialog(const char* title, const char* message) {
		return Utils::ShowDialog(title, message, NMB::Icon::ICON_WARNING);
	}

	NMB::Result MessageDialog::ErrorDialog(const char* title, const char* message) {
		return Utils::ShowDialog(title, message, NMB::Icon::ICON_ERROR);
	}
}


