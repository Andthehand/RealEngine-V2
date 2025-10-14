#include "RealEngine/Core/FileDialogs.h"

#include <filesystem>

#include <gtk/gtk.h>

#define MAX_STRLEN 1024

namespace RealEngine {
    static void AddTypeToFilterName(const char* typebuf, char* filterName, size_t bufsize) {
        const char SEP[] = ", ";

        size_t len = strlen(filterName);
        if (len != 0)
        {
            strncat(filterName, SEP, bufsize - len - 1);
            len += strlen(SEP);
        }

        strncat(filterName, typebuf, bufsize - len - 1);
    }

    int IsFilterSegmentChar(char ch) {
        return (ch == ',' || ch == ';' || ch == '\0');
    }

    static void AddFiltersToDialog(GtkWidget* dialog, const char* filterList) {
        const char* p = filterList;

        if (!filterList)
            return;

        /* Helper to split pattern tokens separated by ';' */
        auto add_patterns_to_filter = [](GtkFileFilter* filter, const char* pattern_token) {
            /* Make a copy because strtok-like parsing needed */
            char buf[MAX_STRLEN];
            strncpy(buf, pattern_token, MAX_STRLEN - 1);
            buf[MAX_STRLEN - 1] = '\0';

            char* saveptr = NULL;
            char* tok = strtok_r(buf, ";", &saveptr);
            while (tok) {
                /* normalize "*.*" to "*" because gtk pattern "*" matches any filename */
                if (strcmp(tok, "*.*") == 0)
                    gtk_file_filter_add_pattern(filter, "*");
                else
                    gtk_file_filter_add_pattern(filter, tok);

                tok = strtok_r(NULL, ";", &saveptr);
            }
            };

        while (*p) {
            /* read display name */
            const char* display_name = p;
            size_t name_len = strlen(display_name);
            p += name_len + 1; /* move past name and its terminating NUL */

            if (*p == '\0') {
                /* odd number of tokens (name without pattern) - break */
                break;
            }

            /* read pattern string */
            const char* pattern_str = p;
            size_t pattern_len = strlen(pattern_str);
            p += pattern_len + 1; /* move past pattern and its terminating NUL */

            /* create and populate filter */
            GtkFileFilter* filter = gtk_file_filter_new();
            gtk_file_filter_set_name(filter, display_name);

            /* add one or more patterns (split on ';') */
            add_patterns_to_filter(filter, pattern_str);

            gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

            /* loop continues; stops when p points to final '\0' (double-NUL) */
        }

        /* always append a wildcard option to the end (if you still want it) */
        GtkFileFilter* allFilter = gtk_file_filter_new();
        gtk_file_filter_set_name(allFilter, "All Files (*.*)");
        gtk_file_filter_add_pattern(allFilter, "*");
        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), allFilter);
    }

    static void WaitForCleanup() {
        while (gtk_events_pending())
            gtk_main_iteration();
    }

    static void SetDefaultPath(GtkWidget* dialog, const char* defaultPath) {
        if (!defaultPath || strlen(defaultPath) == 0)
            return;

        /* GTK+ manual recommends not specifically setting the default path.
           We do it anyway in order to be consistent across platforms.

           If consistency with the native OS is preferred, this is the line
           to comment out. -ml */
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), defaultPath);
    }

	std::filesystem::path FileDialogs::OpenFile(const char* filter) {
        GtkWidget* dialog;
        std::string result;

        if (!gtk_init_check(NULL, NULL)) {
            RE_CORE_ASSERT(false, "GTK failed to initialize!");
            return "";
        }

        dialog = gtk_file_chooser_dialog_new("Open File",
            NULL,
            GTK_FILE_CHOOSER_ACTION_OPEN,
            "_Cancel", GTK_RESPONSE_CANCEL,
            "_Open", GTK_RESPONSE_ACCEPT,
            NULL);

        /* Build the filter list */
        AddFiltersToDialog(dialog, filter);

        /* Set the default path */
        SetDefaultPath(dialog, std::filesystem::current_path().c_str());

        if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
        {
            char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            if (filename) {
                result = filename;
                g_free(filename);
            }
        }

        WaitForCleanup();
        gtk_widget_destroy(dialog);
        WaitForCleanup();

        return result;
	}

    std::filesystem::path FileDialogs::SaveFile(const char* filter) {
        GtkWidget* dialog;
        std::filesystem::path result;

        if (!gtk_init_check(NULL, NULL)) {
            RE_CORE_ASSERT(false, "GTK failed to initialize!");
            return "";
        }

        dialog = gtk_file_chooser_dialog_new("Save File",
            NULL,
            GTK_FILE_CHOOSER_ACTION_SAVE,
            "_Cancel", GTK_RESPONSE_CANCEL,
            "_Save", GTK_RESPONSE_ACCEPT,
            NULL);
        gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);

        /* Build the filter list */
        AddFiltersToDialog(dialog, filter);

        /* Set the default path */
        SetDefaultPath(dialog, std::filesystem::current_path().c_str());

        if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
        {
            char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            if (filename) {
                result = filename;
                g_free(filename);
            }
        }

        WaitForCleanup();
        gtk_widget_destroy(dialog);
        WaitForCleanup();

        return result;
    }
}
