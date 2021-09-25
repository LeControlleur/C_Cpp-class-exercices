#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_utils.h"




//  Ce fichier permet de configurer la base de données
int db_config(MYSQL* con)
{
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

}
