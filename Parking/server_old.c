#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <json-c/json.h>
#include "db_utils.h"
#include "db_config.h"

#define PORT 8888
#define MAX_ENTREE 2
#define MAX_SORTIE 1
#define BUFFER_SIZE 1024
#define TRUE 1

char *is_admin(struct json_object *parsed_json, char *mot_de_passe)
{
    struct json_object *password;
    char *pwd;
    json_object_object_get_ex(parsed_json, "password", &password);

    pwd = "azerty";
    //sprintf(pwd, "%s", password);

    if (strcmp(pwd, mot_de_passe) == 0)
    {
        return "{admin:1}";
    }
    else
    {
        return "{admin:0}";
    }
}

int main(int argc, char *argv[])
{

    //  Structures que nous utiliserons pour la gestion des données sous format JSON
    struct json_object *parsed_json;

    //  Paramètres du parking : 2 entrée, 1 sortie
    int nbre_entree = 0;
    int nbre_sortie = 0;

    /**
     * 
     *      Connexion à la base de données
     * 
     */

    MYSQL *con = NULL;
    con = db_connexion();

    //  Montage de la BD avant le lancement du programme
    MYSQL_RES *res = NULL;
    res = mysql_list_tables(con, NULL);
    if (res == NULL)
    {
        finish_with_error(con);
    }

    if (mysql_num_rows(res) < 3)
    {
        db_config(con);
    }

    /**
     * 
     *      Recupération du mot de passe admin
     * 
     */

    //  Ouverture du fichier de configurations
    FILE *fichier = NULL;
    fichier = fopen(".env", "r");
    if (fichier == NULL)
    {
        perror("fichier de configurations");
        exit(EXIT_FAILURE);
    }

    char buff[256];
    char *mdp_admin;

    char *cle;
    char *valeur;

    while (fgets(buff, sizeof(buff), fichier) != NULL)
    {
        cle = strtok(buff, "=");
        valeur = strtok(NULL, "\n");

        if (strcmp(cle, "ADMIN_PASSWORD") == 0)
        {
            mdp_admin = malloc(strlen(valeur));
            strcpy(mdp_admin, valeur);
        }
        valeur = NULL;
    }

    /***
     * 
     *      Configuration du socket
     * 
     */

    //  On définit un serveur pour 3 clients max qui sont les duex entrées et la sortie
    int opt = TRUE;
    int master_socket, addrlen, new_socket, client_socket[3],
        max_clients = 3, activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[1025]; //  Buffer d'1Kb

    //  Définition de l'ensemle de sockets
    fd_set readfds;

    //  Message de test de la connexion
    char *message = "GestiPark Server \r\n";

    //  Initialisation des valeurs des clients à 0 pour signifier qu'il n sont pas connectés
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    //  Création d'un socket serveur
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Initialisation");
        exit(EXIT_FAILURE);
    }

    //  Définition du serveur pour recevoir plusieurs connections
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0)
    {
        perror("Définition");
        exit(EXIT_FAILURE);
    }

    //  Informations du socket créé
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //  Liaison du socket à l'adresse et au port
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Liaison");
        exit(EXIT_FAILURE);
    }
    printf("Écoute du serveur sur le port %d \n", PORT);

    //  Spécification de 3 connexion max pour le socket maitre
    if (listen(master_socket, 3) < 0)
    {
        perror("écoute");
        exit(EXIT_FAILURE);
    }

    //  Reception de connexions entrantes
    addrlen = sizeof(address);
    printf("En attente de connexion ...\n");

    //  Boucle qui s'exécute tant que le serveur est en activité
    while (TRUE)
    {
        //  Réinitialisation de l'ensemble des sockets
        FD_ZERO(&readfds);

        //  Ajout du socket maitre à l'ensemble
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //  Ajout du socket serveur à l'ensemble
        for (i = 0; i < max_clients; i++)
        {
            //  Descripteur de socket
            sd = client_socket[i];

            //  Vérification la la validaité du descripteur avant l'ajout à l'ensemble
            if (sd > 0)
                FD_SET(sd, &readfds);

            //  Recherche du socket avec le huméro de description le plus élevé
            if (sd > max_sd)
                max_sd = sd;
        }

        //  Attente indéfini de l'activité de l'un des sockets
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            perror("selection");
        }

        //  Reception d'une connexion sur le socket maître
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("nouvelle connexion");
                exit(EXIT_FAILURE);
            }

            //  Affichage des infos de la nouvelle connexion entrante
            printf("Nouvelle connexion , n° d socket : %d , adresse ip : %s , port : %d \n ", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            //  Ajout du nouveau socket à au tableau des clients
            for (i = 0; i < max_clients; i++)
            {
                //  On vérifie si la place est vide
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    printf("Ajout du socket à la position %d\n", i);

                    break;
                }
            }
        }

        //  Reception d'un message au socket maitre
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds))
            {
                //  Vérification du message pour savoir si c'est un message de déconnexion
                //incoming message
                if ((valread = read(sd, buffer, 1024)) == 0)
                {
                    //  Affichage des infos enc as de messag de déconnexion
                    getpeername(sd, (struct sockaddr *)&address,
                                (socklen_t *)&addrlen);
                    printf("Client déconnecté , ip %s , port %d \n",
                           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    //  Fermeture du socket et réinitialisation à 0 dans le tableau des clients
                    close(sd);
                    client_socket[i] = 0;
                }

                //  Traitement du message reçu
                else
                {
                    //  Recepetion de la réponse
                    buffer[valread] = '\0';
                    printf("Message reçu : %s\n", buffer);

                    sprintf(buffer, "Réponse depuis le serveur\0");
                    send(sd , buffer , strlen(buffer) , 0 );

                    /*
                    //  Chaine comprenant le résultat qui sera envoyé au client
                    char* response  = "Je suis bien là!!!\0";

                    printf("On retourne : %s\n", response);
                    send(sd, response, BUFFER_SIZE, 0);
                    */
                }
            }
        }
    }

    return 0;
}
