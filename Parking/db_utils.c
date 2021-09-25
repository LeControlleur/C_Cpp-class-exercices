#include <mysql/mysql.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_utils.h"

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

MYSQL *db_connexion()
{

    //  Ouverture du fichier de configurations
    FILE *fichier = NULL;
    fichier = fopen(".env", "r");
    if (fichier == NULL)
    {
        printf("L'ouverture du fichier de configurations a échoué !!");
        exit(1);
    }

    struct db_info
    {
        char *host;
        char *user;
        char *passwd;
        char *database;
        int port;
    };

    struct db_info database;
    //  Enregistrement de valeurs par défaut
    database.host = "localhost";
    database.port = 0;

    /*
    Les variables de l'environnement local sont : 
    MYSQL_HOST
    MYSQL_USER
    MYSQL_PASSWORD
    MYSQL_DATABASE
    MYSQL_PORT
    */

    char buff[256];
    char *cle;
    char *valeur;

    while (fgets(buff, sizeof(buff), fichier) != NULL)
    {
        cle = strtok(buff, "=");
        valeur = strtok(NULL, "\n");

        if (strcmp(cle, "MYSQL_HOST") == 0)
        {
            database.host = malloc(strlen(valeur));
            strcpy(database.host, valeur);
        }
        else if (strcmp(cle, "MYSQL_USER") == 0)
        {
            database.user = malloc(strlen(valeur));
            strcpy(database.user, valeur);
        }
        else if (strcmp(cle, "MYSQL_PASSWORD") == 0)
        {
            database.passwd = malloc(strlen(valeur));
            strcpy(database.passwd, valeur);
        }
        else if (strcmp(cle, "MYSQL_DATABASE") == 0)
        {
            database.database = malloc(strlen(valeur));
            strcpy(database.database, valeur);
        }
        else if (strcmp(cle, "MYSQL_PORT") == 0)
        {
            database.port = atoi(valeur);
        }
        else
        {
        }
        valeur = NULL;
    }

    //  Création d'une instance de base de données
    MYSQL *con = NULL;

    con = mysql_init(con);

    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    //  Connexion à la base de données
    //if (mysql_real_connect(con, database.host, database.user, database.passwd, database.database, database.port, NULL, 0) == NULL)

    if (mysql_real_connect(con, "localhost", "master1", "master1", "gestion_parking", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }

    fclose(fichier);

    return con;
}

MYSQL_RES *db_get_all(char *table, MYSQL *con)
{

    char *query_str;
    query_str = "SELECT ALL FROM TypeVehicule";
    /*
    query_str = malloc(strlen("SELECT ALL FROM TypeVehicule") + strlen(table));
    strcpy(query_str, "SELECT ALL FROM ");
    printf(query_str);
    strcat(query_str, table);
    printf(query_str);
    */

    //  Exécution de la requête
    if (!mysql_query(con, query_str))
    {
        finish_with_error(con);
    }

    //  Recupération des résultats
    MYSQL_RES *res;
    res = mysql_store_result(con);

    return res;
}

