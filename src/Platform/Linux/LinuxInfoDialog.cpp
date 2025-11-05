#include "RealEngine/Core/Dialogs.h"

#include <gtk/gtk.h>

namespace RealEngine {
    void InfoDialog::WarnUser(const std::string& title, const std::string& message) {
        if (!gtk_init_check(NULL, NULL)) {
            RE_CORE_ASSERT(false, "GTK failed to initialize!");
            return;
        }

        GtkWidget* dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_USE_HEADER_BAR,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_CLOSE,
            message.c_str());

        gtk_window_set_title(GTK_WINDOW(dialog), title.c_str());

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}