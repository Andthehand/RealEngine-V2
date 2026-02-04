#pragma once
#include <NMB/NMB.h>

namespace RealEngine {
	class MessageDialog {
	public:
		static NMB::Result InfoDialog(const char* title, const char* message);
		static NMB::Result WarnDialog(const char* title, const char* message);
		static NMB::Result ErrorDialog(const char* title, const char* message);
	};
}
