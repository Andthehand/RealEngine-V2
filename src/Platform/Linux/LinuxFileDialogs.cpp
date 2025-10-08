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
        GtkFileFilter* filter;
        char typebuf[MAX_STRLEN] = { 0 };
        const char* p_filterList = filterList;
        char* p_typebuf = typebuf;
        char filterName[MAX_STRLEN] = { 0 };

        if (!filterList || strlen(filterList) == 0)
            return;

        filter = gtk_file_filter_new();
        while (1) {
            if (IsFilterSegmentChar(*p_filterList)) {
                char typebufWildcard[MAX_STRLEN];
                /* add another type to the filter */
                RE_CORE_ASSERT(strlen(typebuf) > 0, "typebuf should not be empty");
                RE_CORE_ASSERT(strlen(typebuf) < MAX_STRLEN - 1, "typebuf length exceeds limit");

                snprintf(typebufWildcard, MAX_STRLEN, "*.%s", typebuf);
                AddTypeToFilterName(typebuf, filterName, MAX_STRLEN);

                gtk_file_filter_add_pattern(filter, typebufWildcard);

                p_typebuf = typebuf;
                memset(typebuf, 0, sizeof(char) * MAX_STRLEN);
            }

            if (*p_filterList == ';' || *p_filterList == '\0') {
                /* end of filter -- add it to the dialog */

                gtk_file_filter_set_name(filter, filterName);
                gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

                filterName[0] = '\0';

                if (*p_filterList == '\0')
                    break;

                filter = gtk_file_filter_new();
            }

            if (!IsFilterSegmentChar(*p_filterList)) {
                *p_typebuf = *p_filterList;
                p_typebuf++;
            }

            p_filterList++;
        }

        /* always append a wildcard option to the end*/

        filter = gtk_file_filter_new();
        gtk_file_filter_set_name(filter, "*.*");
        gtk_file_filter_add_pattern(filter, "*");
        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);
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

	std::string FileDialogs::OpenFile(const char* filter) {
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

        result = "";
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
