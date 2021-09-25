#include <gtk/gtk.h>
#include "win_function.h"

/*
* #include<string.h> for the strlen() function...
*/
void set_window_background(gchar *__imgPath__)
{
    /*
* Malloc a buffer to store the css data and fill it with css code
*/
    gchar *css = (gchar *)malloc((strlen(__imgPath__) + 55) * sizeof(gchar));
    sprintf(css, "GtkWindow{\nbackground-image: url('%s');\n}\n", __imgPath__);
    /*
* Create a css provider and add pass css data to it
*/
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    /*
* Bind the css provider for the current display
*/
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    /*
* Free the used memory...
*/
    g_object_unref(provider);
    g_free(css);
}