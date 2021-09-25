#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "win_function.h"



int main(int argc, char **argv)
{

    //  Initialisation de la librairie gtk
    gtk_init(&argc, &argv);

    //  Creation de la fenêtre
    GtkWidget *MainWindow = NULL;
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //  Définition du titre
    gtk_window_set_title(GTK_WINDOW(MainWindow), "GestiPark");
    //  Définition des dimensions
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 700, 500);
    //  Positionnement au centre de l'écran
    gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);
    //  Empecher la modification de la taille
    gtk_window_set_resizable(GTK_WINDOW(MainWindow), false);
    //  Définition de l'icone
    if (!gtk_window_set_icon_from_file(GTK_WINDOW(MainWindow), "parking.png", NULL))
    {
        printf("L'icone n'a pas être définie");
    }

    //  Chaque écran sera reprsenté par un  widget
    GtkWidget *EcranPrincipal = NULL;
    GtkWidget *GrilleEcranPrincipal = NULL;
    

    //  --------    Ecran principal     -------------
    EcranPrincipal = gtk_box_new(TRUE, 0);
    GrilleEcranPrincipal = gtk_grid_new();



    //  Message d'accueil
    GtkWidget *message_accueil = NULL;
    //  Conversion de la chaine avec les balises
    message_accueil = gtk_label_new("<span size=\"xx-large\"><b>Bienvenue dans <i>GestiPark</i></b></span>\n\n <span size=\"x-large\"><b>Votre outils de gestion de parking fait intégralement en C</b></span>\n\nGestiPark est un outils qui vous permettra de gérer les entrées et sortie des véhicules de \nvotre parking d'une manière tellement facile que vous n'en reviendrez pas.\n\n\n\n\n\n<span size=\"x-large\">Veuillez selectionner votre poste</span>");

    //  On spécifie l'utilisation d'une convertion
    gtk_label_set_use_markup(GTK_LABEL(message_accueil), TRUE);

    gtk_label_set_justify(GTK_LABEL(message_accueil), GTK_JUSTIFY_CENTER);

    gtk_grid_attach(GTK_GRID(GrilleEcranPrincipal), message_accueil, 2, 1, 5, 2);

    gtk_container_add(GTK_CONTAINER(EcranPrincipal), message_accueil);



    //  Afichage des bouttons de menu

    GtkWidget *button_entree;
    GtkWidget *button_sortie;

    //  Box des boutons
    GtkWidget *box_boutons;

    //  Initialisation des boutons
    //  button_entree = gtk_button_new_with_label ("ENTREE");
    //  button_sortie = gtk_button_new_with_label ("SORTIE");

    button_entree = gtk_box_new();
    button_sortie = gtk_box_new();

    //  Box qui contiendra les boutons
    box_boutons = gtk_box_new(FALSE, 20);

    //  Ajout des boutons à leur box
    gtk_container_add(GTK_CONTAINER(box_boutons), button_entree);
    gtk_container_add(GTK_CONTAINER(box_boutons), button_sortie);

    gtk_container_add(GTK_CONTAINER(EcranPrincipal), box_boutons);


    //  On ajoute l'écran principal à la fenêtre
    gtk_container_add(GTK_CONTAINER(MainWindow), GrilleEcranPrincipal);

    //  Destruction de la fenêtre lorsque l'évènement est déclenché
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    //  Affichage de la boucle évènementielle
    gtk_widget_show_all(MainWindow);
    gtk_main();

    return EXIT_SUCCESS;
}