#include "RealEngine/Core/Dialogs.h"

#include <WinUser.h>

namespace RealEngine {
	void InfoDialog::WarnUser(const std::string& title, const std::string& message) {
		RE_PROFILE_FUNCTION();

        MessageBox(
            NULL,
            message.c_str(),
            title.c_str(),
            MB_ICONWARNING | MB_OK | MB_DEFBUTTON1
        );
	}
}