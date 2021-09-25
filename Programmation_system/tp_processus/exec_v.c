#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    /* Tableau de char contenant les arguments (là aucun : le nom du
    programme et NULL sont obligatoires) */
    char *arguments[] = { "ps", NULL };
    /* Lancement de la commande */
    if (execv("/bin/ps", arguments) == -1) {
        perror("execv");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}