#include <mysql/mysql.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "db_utils.h"
#include "affichage.h"

unsigned int i;

void affichage_types_vehicules(MYSQL *con)
{
    //  Exécution de la requête

    printf("Affichage des types de véhicule");
    /*
    MYSQL_RES *res;
    res = db_get_all("TypeVehicule", con);
    if (res)
    {
        unsigned int nbre_cols;
        nbre_cols = mysql_num_fields(res);

        printf("Les types de véhicule sont : ");

        //  Affichage des résultats ligne par
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)))
        {
            unsigned long *lengths;
            lengths = mysql_fetch_lengths(res);
            for (i = 0; i < nbre_cols; i++)
            {
                printf("[%.*s] ", (int)lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
    }
    else
    {
        printf("\nAucun resultat");
    }

    mysql_free_result(res);
    */
}

void affichage_vehicules(MYSQL *con)
{
}

void affichage_tickets(MYSQL *con)
{
}

void affichage_infos(MYSQL *con)
{

    bool reset = true;
    while (reset)
    {
        printf("\n\n\t\t\t\tMENU AFFICHAGE\n\n");
        printf("\n\t\t\t1-    Types de véhicules");
        printf("\n\t\t\t2-    Véhicules");
        printf("\n\t\t\t3-    Tickets emis");
        printf("\n\t\t\t0-    RETOUR");

        //  Affichage des informations des informations

        int menu;

        printf("\n\n\t\t\t\t==> ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            affichage_types_vehicules(con);
            break;

        case 2:
            affichage_vehicules(con);
            break;

        case 3:
            affichage_tickets(con);
            break;

        case 0:
            reset = false;
            break;

        default:
            printf("\nChoix incorrect !!!!\n");
            break;
        }
    }
}
