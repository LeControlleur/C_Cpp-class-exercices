#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

//  Ce fichier permet de configurer la base de données
int main(int argc, char **argv)
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
            database.host = valeur;
            printf("Host : %s", database.host);
        }
        else if (strcmp(cle, "MYSQL_USER") == 0)
        {
            database.user = valeur;
        }
        else if (strcmp(cle, "MYSQL_PASSWORD") == 0)
        {
            database.passwd = valeur;
        }
        else if (strcmp(cle, "MYSQL_DATABASE") == 0)
        {
            database.database = valeur;
        }
        else if (strcmp(cle, "MYSQL_PORT") == 0)
        {
            database.port = atoi(valeur);
        }
        else
        {
        }
    }
    


    fclose(fichier);

    
    //  Création d'une instance de base de données
    MYSQL *con = NULL;

    con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    printf("Port => %d", database.port);

    //  Connexion à la base de données
    if (mysql_real_connect(con, database.host, database.user, database.passwd, database.database, database.port, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }

    //  Creation de la base de données
    /*
    char *query = "CREATE DATABASE gestion_parking";
    if (mysql_query(con, query))
    {
        finish_with_error(con);
    }
    */

    //  Creation des différentes tables de la BD

    char *query = "CREATE TABLE IF NOT EXISTS TypeVehicule (id INT PRIMARY KEY AUTO_INCREMENT, caracteristique VARCHAR(255), prix_place FLOAT, nbre_place_total INT, nbre_place_dispo FLOAT) ENGINE=InnoDB ";
    if (mysql_query(con, query))
    {
        finish_with_error(con);
    }

    query = "CREATE TABLE IF NOT EXISTS Vehicule (id INT PRIMARY KEY AUTO_INCREMENT, marque VARCHAR(255), matricule VARCHAR(255),type_vehicule INT, CONSTRAINT fk_type_vehicule FOREIGN KEY(type_vehicule) REFERENCES TypeVehicule(id) ) ENGINE=InnoDB";
    if (mysql_query(con, query))
    {
        finish_with_error(con);
    }

    query = "CREATE TABLE IF NOT EXISTS Ticket (id INT PRIMARY KEY AUTO_INCREMENT, numero_ticket VARCHAR(255) NOT NULL, prix_stationnement FLOAT, heure_entree TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, heure_sortie TIMESTAMP, vehicule INT, place_normale BOOLEAN NOT NULL DEFAULT TRUE, CONSTRAINT fk_vehicule FOREIGN KEY(vehicule) REFERENCES Vehicule(id) ) ENGINE=InnoDB ";
    if (mysql_query(con, query))
    {
        finish_with_error(con);
    }

    printf("Elaboration de la base de données terminée !!! \n");
}