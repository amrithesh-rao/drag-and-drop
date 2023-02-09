#include <glib.h>
#include <gtk/gtk.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    GtkWidget *dialog;
    GList *uris, *l;
    gchar *uri;
    gchar *filename;

    gtk_init(&argc, &argv);

    dialog = gtk_file_chooser_dialog_new("Select a file or folder", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        uris = gtk_file_chooser_get_uris(GTK_FILE_CHOOSER(dialog));
        for (l = uris; l != NULL; l = l->next) {
            uri = l->data;
            filename = g_filename_from_uri(uri, NULL, NULL);
            if (filename != NULL) {
                printf("Selected file/folder: %s\n", filename);
                g_free(filename);
            }
            g_free(uri);
        }
        g_list_free(uris);
    }
    gtk_widget_destroy(dialog);

    return 0;
}
