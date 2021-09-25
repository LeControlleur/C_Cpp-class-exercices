#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <time.h>
#include <math.h>

/**
 * \brief Ce programme permet la gestion d'un parking. Le programme a totalement été programmé en C
 * 
 * \author Samuel Bini, Florence Yao
 * 
 * \version 1.0.0
 * 
 * \date 29/04/2021
 * 
 */

static char host[255] = "localhost";
static char user[255] = "master1";
static char pass[255] = "master1";
static char dbname[255] = "gestion_parking";

static unsigned int port = 3306;

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

//INSERTION ENGIN A DEUX ROUES
/**
     * 
     * \fn void insertion() 
     * 
     * \brief Fonction permettant l'insertion d'un engin à deux roues dans le parking
     * 
     */
void insertion()
{

    printf("\n\t\tINSERTION D'UN VEHICULE A DEUX ROUES\n\n");

    int h, min, s, day, mois, an;
    time_t now;

    time(&now);
    struct tm *local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;
    printf("Le véhicule à deux roues a été enregistré le %02d/%02d/%d à %02d:%02d\n", day, mois, an, h, min);

    //int id_livre;
    //char type1[25];
    char matricule1[25];
    //char date_entre1[25] = "timelocal";
    //char date_sortie1[25] = "timelocal";
    char query[255];
    char autre[255];

    //printf("Veuillez saisir le type de votre engin :\n");
    //scanf("%s", type1);
    printf("\tMATRICULE : ");
    scanf("%s", matricule1);
    //printf(timezone);
    //printf("%s", libelle);
    conn = mysql_init(NULL);

    if (!(mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)))
    {
        fprintf(stderr, "\n Error: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }

    sprintf(query, "INSERT INTO engin_deux_roues (matricule, date_entre, date_sortie, temps_passe_parking) VALUES('%s' , %ld, NULL, NULL);", matricule1, time(&now));

    if (!mysql_query(conn, query))
    {
        printf("error : %s\n", mysql_error(conn));
    }

    sprintf(autre, "SELECT nbre FROM nbr_engin WHERE cat = '2 roues';");

    if (!mysql_query(conn, autre))
    {
        printf("error : %s\n", mysql_error(conn));
    }

    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        if (atoi(row[0]) > 0)
        {

            sprintf(autre, "UPDATE nbr_engin SET nbre = nbre - 1 WHERE cat = '2 roues'");
            if (!mysql_query(conn, autre))
            {
                printf("error : %s\n", mysql_error(conn));
            }
            else
            {
                printf("\nEnregistrement réussi\n\n");
            }
        }
        else
        {
            printf("===> Désolé !!!! Il n'y a plus de places pour les véhicules à deux roues dans le parking!!! \n");
        }
    }
}

/**
     * 
     * \fn void insertion_vehicule()
     * 
     * \brief Fonction permettant l'insertion d'une voiture classique dans le parking
     * 
     */
//INSERTION VEHICULE
void insertion_vehicule()
{

    int h, min, s, day, mois, an;
    time_t now;

    time(&now);
    struct tm *local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;
    printf("La voiture a été enregistré le %02d/%02d/%d à %02d:%02d\n", day, mois, an, h, min);

    char matricule1[25];
    char query[255];
    char autre[255];

    //printf("Veuillez saisir le type de votre engin :\n");
    //scanf("%s", type1);
    printf("MATRICULE : ");
    scanf("%s", matricule1);
    //printf(timezone);
    //printf("%s", libelle);
    conn = mysql_init(NULL);

    if (!(mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)))
    {
        fprintf(stderr, "\n Error: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }
    sprintf(query, "INSERT INTO engin_vehicule (matricule, date_entre, date_sortie, temps_passe_parking) VALUES('%s' , '%ld', '%d', '%d');", matricule1, time(&now), 1614903463, 1614903463);

    if (!mysql_query(conn, query))
    {
        printf("error");
    }

    sprintf(autre, "SELECT * FROM nbr_engin;");
    if (!mysql_query(conn, autre))
    {
        printf("error");
    }
    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {

        if (atoi(row[2]) > 0)
        {
            sprintf(autre, "UPDATE nbr_engin SET nbr_vehicule = nbr_vehicule - 1");
            if (!mysql_query(conn, autre))
            {
                printf("error");
            }
        }

        else if (atoi(row[3]) - 1 > 0)
        {
            printf("Il n'y a plus de place pour les voitures classiques. Vous pouvez prendre une place pour les camions.\n");
            sprintf(autre, "UPDATE nbr_engin SET nbr_camion = nbr_camion - 1");
            if (!mysql_query(conn, autre))
            {
                printf("error");
            }
        }

        else
        {
            printf("===> Désolé !!!! Il n'y a plus de places pour les voitures classiques dans le parking!!! \n");
        }

        exit(EXIT_SUCCESS);
    }
}

/**
     * 
     * \fn void void insertion_camion()
     * 
     * \brief Fonction permettant l'insertion d'un camion dans le parking
     * 
     */
void insertion_camion()
{

    int h, min, s, day, mois, an;
    time_t now;

    time(&now);
    struct tm *local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;
    printf("Le camion a été enregistré le %02d/%02d/%d à %02d:%02d\n", day, mois, an, h, min);

    //int id_livre;
    //char type1[25];
    char matricule1[25];
    //char date_entre1[25] = "timelocal";
    //char date_sortie1[25] = "timelocal";
    char query[255];
    char autre[255];

    //printf("Veuillez saisir le type de votre engin :\n");
    //scanf("%s", type1);
    printf("MATRICULE :\n");
    scanf("%s", matricule1);
    //printf(timezone);
    //printf("%s", libelle);
    conn = mysql_init(NULL);

    if (!(mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)))
    {
        fprintf(stderr, "\n Error: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }
    sprintf(query, "INSERT INTO engin_camion (matricule, date_entre, date_sortie, temps_passe_parking) VALUES('%s' , '%ld', '%d', '%d');", matricule1, time(&now), 1614903463, 1614903463);

    if (mysql_query(conn, query))
    {
        printf(":-(");
    }

    sprintf(autre, "SELECT * FROM nbr_engin;");
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }
    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {

        if (atoi(row[3]) > 0)
        {

            sprintf(autre, "UPDATE nbr_engin SET nbr_camion = nbr_camion - 1");
            if (mysql_query(conn, autre))
            {
                printf(":-(");
            }
        }
        else
        {
            printf("===> Désolé !!!! Il n'y a plus de places pour le camion dans le parking!!! \n");
        }
        exit(EXIT_SUCCESS);
    }
}

/**
     * 
     * \fn void void affiche()
     * 
     * \brief Fonction permettant d'afficher les véhicules à deux roues présents dans le parking
     * 
     */
void affiche()
{

    mysql_query(conn, "SELECT * FROM engin_deux_roues");
    res = mysql_store_result(conn);

    printf("id\timmatriculation\t\tdate entree\n");
    while (row = mysql_fetch_row(res))
    {
        printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(res);
    mysql_close(conn);
}

/**
     * 
     * \fn void affiche_vehicule()
     * 
     * \brief Fonction permettant d'afficher les voitures classiques présentes dans le parking
     * 
     */
void affiche_vehicule()
{
    mysql_query(conn, "SELECT * FROM engin_vehicule");
    res = mysql_store_result(conn);

    printf("|Id|\t\tImmatriculation|\t\tDate entree\n");
    while (row = mysql_fetch_row(res))
    {
        printf("|%s|\t\t%s|\t\t%s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(res);
    mysql_close(conn);
}

/**
     * 
     * \fn void affiche_camion()
     * 
     * \brief Fonction permettant d'afficher les camions présents dans le parking
     * 
     */
void affiche_camion()
{
    mysql_query(conn, "SELECT * FROM engin_camion");
    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(res);
    mysql_close(conn);
}

/**
     * 
     * \fn void affiche_nbr_engin()
     * 
     * \brief Fonction permettant d'afficher le nombre de places disponibles dans le parking
     * 
     */
void affiche_nbr_engin()
{
    mysql_query(conn, "SELECT * FROM FROM nbr_engin");
    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        //printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
        printf("====>Nombre de place pour les engins a deux roues: %s \n", row[0]);
        printf("====>Nombre de place pour les engins vehicules: %s \n", row[1]);
        printf("====>Nombre de place pour les engins camions: %s \n", row[2]);
    }
    mysql_free_result(res);
    mysql_close(conn);
}

/**
     * 
     * \fn void sortie_engin_deux_roues()
     * 
     * \brief Fonction permettant de supprimer un engin à deux roues de la BD à la sortie du parking
     * 
     */
void sortie_engin_deux_roues()
{
    char matri[25];
    char autre[255];
    double total_tmp;
    int som_pay;
    float nbr_min;
    int dif;

    int h, min, s, day, mois, an;
    time_t now;

    // Renvoie l'heure actuelle
    time(&now);
    // Convertir au format heure locale
    //printf("Aujourd'hui est : %s", ctime(&now));
    struct tm *local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;
    printf("L'engin à deux roues est sortie le %02d/%02d/%d à %02d:%02d\n", day, mois, an, h, min);

    printf("IMMATRICULATION : ");
    scanf("%s", matri);

    sprintf(autre, "SELECT * FROM engin_deux_roues WHERE matricule ='%s';", matri);
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }
    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        printf("ENGIN A DEUX ROUES D'IMMATRICULATION %s", row[1]);
        printf(" DEMANDE A SORTIR \n");
        printf("\n");

        sprintf(autre, "UPDATE engin_deux_roues SET date_sortie = '%ld' WHERE matricule = '%s';", time(&now), matri);
        if (mysql_query(conn, autre))
        {
            printf(":-( ECHEC UPDATE\n");
        }

        dif = (time(&now) - atoi(row[2]));

        sprintf(autre, "UPDATE engin_deux_roues SET temps_passe_parking = '%d' WHERE matricule = '%s';", dif, matri);
        if (mysql_query(conn, autre))
        {
            printf(":-( ECHEC UPDATE\n");
        }

        if (dif <= 86399)
        {
            total_tmp = dif;
            som_pay = ceil((total_tmp / 3600)) * 500;
            nbr_min = (total_tmp / 60);
            printf("Votre engin à deux roues a passé: %f ", nbr_min);
            printf("minutes dans notre Parking \n");
            printf("La somme à payer est : %d ", som_pay);
            printf("FCFA \n");
            printf("\n");
            printf("AU REVOIR ET A BIENTOT !!!!!!!!!!!!!! \n");
        }
        if (dif >= 86400)
        {
            total_tmp = dif;
            som_pay = ceil((total_tmp / 3600)) * 20000;
            nbr_min = (total_tmp / 60);
            printf("Votre engin à deux roues a passé: %f ", nbr_min);
            printf("minutes dans notre Parking \n");
            printf("La somme à payer est : %d ", som_pay);
            printf("FCFA \n");
            printf("\n");
            printf("AU REVOIR ET A BIENTOT !!!!!!!!!!!!!! \n");
        }
    }

    sprintf(autre, "UPDATE nbr_engin SET nbr_moto = nbr_moto+ 1");
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }

    sprintf(autre, "DELETE FROM engin_deux_roues WHERE matricule = '%s';", matri);
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }
}

/**
     * 
     * \fn void sortie_engin_vehicule()
     * 
     * \brief Fonction permettant de supprimer une voiture de la BD à la sortie du parking
     * 
     */
void sortie_engin_vehicule()
{
    char matri[25];
    char autre[255];
    double total_tmp;
    int som_pay;
    float nbr_min;
    int dif;

    int h, min, s, day, mois, an;
    time_t now;

    // Renvoie l'heure actuelle
    time(&now);
    // Convertir au format heure locale
    //printf("Aujourd'hui est : %s", ctime(&now));
    struct tm *local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;
    printf("La voiture est sortie le %02d/%02d/%d à %02d:%02d\n", day, mois, an, h, min);

    printf("IMMATRICULATION : ");
    scanf("%s", matri);

    sprintf(autre, "SELECT * FROM engin_vehicule WHERE matricule ='%s';", matri);
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }
    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        printf("La voiture %s", row[1]);
        printf(" demande à sortir.\n");
        printf("\n");

        sprintf(autre, "UPDATE engin_vehicule SET date_sortie = '%ld' WHERE matricule = '%s';", time(&now), (matri));
        if (mysql_query(conn, autre))
        {
            printf(":-( ECHEC UPDATE\n");
        }

        dif = (time(&now) - atoi(row[2]));

        sprintf(autre, "UPDATE engin_vehicule SET temps_passe_parking = '%d' WHERE matricule = '%s';", dif, (matri));
        if (mysql_query(conn, autre))
        {
            printf(":-( ECHEC UPDATE\n");
        }

        if (dif <= 86399)
        {
            total_tmp = dif;
            som_pay = ceil((total_tmp / 3600)) * 500;
            nbr_min = (total_tmp / 60);
            printf("Votre voiture a passé: %f ", nbr_min);
            printf("minutes dans notre parking \n");
            printf("La somme à payer est : %d ", som_pay);
            printf("FCFA \n");
            printf("\n");
            printf("AU REVOIR ET A BIENTOT !!!!!!!!!!!!!! \n");
        }
        if (dif >= 86400)
        {
            total_tmp = dif;
            som_pay = ceil((total_tmp / 3600)) * 20000;
            nbr_min = (total_tmp / 60);
            printf("Votre voiture a passé: %f ", nbr_min);
            printf("minutes dans notre parking \n");
            printf("La somme à payer est : %d ", som_pay);
            printf("FCFA \n");
            printf("\n");
            printf("AU REVOIR ET A BIENTOT !!!!!!!!!!!!!! \n");
        }
    }

    sprintf(autre, "UPDATE nbr_engin SET nbr_vehicule = nbr_vehicule + 1");
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }

    sprintf(autre, "DELETE FROM engin_vehicule WHERE matricule = '%s';", matri);
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }

    exit(EXIT_SUCCESS);
}

/**
     * 
     * \fn void sortie_engin_camion()
     * 
     * \brief Fonction permettant de supprimer un camion de la BD à la sortie du parking
     * 
     */
void sortie_engin_camion()
{
    char matri[25];
    char autre[255];
    double total_tmp;
    int som_pay;
    float nbr_min;
    int dif;

    int h, min, s, day, mois, an;
    time_t now;

    // Renvoie l'heure actuelle
    time(&now);
    // Convertir au format heure locale
    //printf("Aujourd'hui est : %s", ctime(&now));
    struct tm *local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;
    printf("La voiture est sortie le %02d/%02d/%d à %02d:%02d\n", day, mois, an, h, min);

    printf("IMMATRICULATION : ");
    scanf("%s", matri);

    sprintf(autre, "SELECT * FROM engin_camion WHERE matricule ='%s';", matri);
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }
    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        printf("LE CAMION D'IMMATRICULATION %s", row[1]);
        printf(" DEMANDE A SORTIR \n");
        printf("\n");

        sprintf(autre, "UPDATE engin_camion SET date_sortie = '%ld' WHERE matricule = '%s';", time(&now), (matri));
        if (mysql_query(conn, autre))
        {
            printf(":-( ECHEC UPDATE\n");
        }

        dif = (time(&now) - atoi(row[2]));

        sprintf(autre, "UPDATE engin_camion SET temps_passe_parking = '%d' WHERE matricule = '%s';", dif, (matri));
        if (mysql_query(conn, autre))
        {
            printf(":-( ECHEC UPDATE\n");
        }

        if (dif <= 86399)
        {
            total_tmp = dif;
            som_pay = ceil((total_tmp / 3600)) * 500;
            nbr_min = (total_tmp / 60);
            printf("Votre camion a passé: %f ", nbr_min);
            printf("minutes dans notre parking \n");
            printf("La somme à payer est : %d ", som_pay);
            printf("FCFA \n");
            printf("\n");
            printf("AU REVOIR ET A BIENTOT !!!!!!!!!!!!!! \n");
        }
        if (dif >= 86400)
        {
            total_tmp = dif;
            som_pay = ceil((total_tmp / 3600)) * 20000;
            nbr_min = (total_tmp / 60);
            printf("Votre camion a passé: %f ", nbr_min);
            printf("minutes dans notre parking \n");
            printf("La somme à payer est : %d ", som_pay);
            printf("FCFA \n");
            printf("\n");
            printf("AU REVOIR ET A BIENTOT !!!!!!!!!!!!!! \n");
        }
    }

    sprintf(autre, "UPDATE nbr_engin SET nbr_camion = nbr_camion + 1");
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }

    sprintf(autre, "DELETE FROM engin_camion WHERE matricule = '%s';", matri);
    if (mysql_query(conn, autre))
    {
        printf(":-(");
    }

    exit(EXIT_SUCCESS);
}

/**
     * 
     * \fn int main()
     * 
     * \brief Fonction principale de la getion du parking qui fait appelle à toutes les autres fonctions
     * 
     */
int main()

{

    conn = mysql_init(NULL);

    if (!(mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)))
    {
        fprintf(stderr, "\n Error: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }

    printf("==========================		GESTION DE PARKING				==========================\n\n");

    int choix;
    int choix2;
    int choix3;
    int choix4;

    do
    {

        printf("\t\tMENU PRINCIPAL\n\n");
        printf("\t1- GERER LES ENTREES\n"); // ajouter l'élément et trier la liste
        printf("\t2- GERER LES SORTIES\n");
        printf("\t3- AFFICHER LE NOMBRE DE PLACES DANS LE PARKING\n");
        printf("\t4- AFFICHER LES ENGINS \n\n");
        printf("\t0- QUITTER \n\n");

        printf("\t\t=====> ");
        scanf("%i", &choix);

        switch (choix)
        {
        case 1:
            do
            {
                printf("\tGESTION DES ENTREES\n\n");
                printf("\t1- ENGIN A 2 ROUES \n");
                printf("\t2- VOITURES CLASSIQUES \n");
                printf("\t3- CAMIONS\n");
                printf("\t0- RETOUR\n");
                printf("\t\t=====> ");
                scanf("%i", &choix2);

                switch (choix2)
                {
                case 1:
                    printf("ARRIVEE D'UN ENGIN A DEUX ROUES\n");
                    insertion();
                    //affiche();
                    break;

                case 2:
                    printf("ARRIVEE D'UNE VOITURE CLASSIQUE\n");
                    insertion_vehicule();
                    //affiche_vehicule();
                    break;

                case 3:
                    printf("ARRIVEE D'UN CAMION\n");
                    insertion_camion();
                    //affiche_camion();
                    break;
                case 0:
                    break;
                default:
                    system("cls");
                    printf("VEUILLEZ ENTRER UN NOMBRE CORRECT \n");
                    break;
                }

            } while (choix2 != 0);
            getchar();

            break;

        case 2:
            do
            {
                printf("\tGESTION DES SORTIES\n\n");
                printf("\t1- ENGIN A 2 ROUES \n");
                printf("\t2- VOITURES CLASSIQUES \n");
                printf("\t3- CAMIONS\n");
                printf("\t0- RETOUR\n");
                printf("\t\t=====> \n");
                scanf("%i", &choix3);

                switch (choix3)
                {
                case 1:
                    printf("Bonne route !!!!!\n");
                    sortie_engin_deux_roues();

                    //affiche();
                    break;

                case 2:
                    printf("Bonne route !!!!!\n");
                    sortie_engin_vehicule();
                    break;

                case 3:
                    printf("Bonne route !!!!!\n");
                    sortie_engin_camion();
                    break;
                case 0:
                    break;
                default:
                    system("cls");
                    printf("VEUILLEZ ENTRER UN NOMBRE CORRECT \n");
                    break;
                }

            } while (choix2 != 0);
            break;

        case 3:
            system("cls");
            printf("\tAFFICHAGE DU NOMBRE DE PLACES DANS LE PARKING\n");
            affiche_nbr_engin();
            break;

        case 4:
            printf("\tAFFICHAGE DES ENGINS DANS LE PARKING \n");

            do
            {
                printf("\t1- ENGIN A 2 ROUES \n");
                printf("\t2- VOITURES CLASSIQUES \n");
                printf("\t3- CAMIONS\n");
                printf("\t0- RETOUR\n");
                printf("\t\t=====> ");
                scanf("%i", &choix4);

                switch (choix4)
                {
                case 1:
                    printf("\t\tAFFICHAGE DES ENGIN A ROUES\n");
                    affiche();
                    break;

                case 2:
                    printf("\t\tAFFICHAGE DES VOITURES A DEUX ROUES \n");
                    affiche_vehicule();
                    break;

                case 3:
                    printf("\t\tAFFICHAGE DE CAMION \n");
                    affiche_camion();
                    break;
                case 0:
                    break;
                default:
                    system("cls");
                    printf("VEUILLEZ ENTRER UN NOMBRE CORRECT \n");
                    break;
                }

            } while (choix4 != 0);

            break;

        case 0:
            break;

        default:
            system("cls");
            printf("VEUILLEZ ENTRER UN NOMBRE CORRECT \n");
            break;
        }

    } while (choix != 0);

    return 0;
}
