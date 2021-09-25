#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
int main(void)
{
    pid_t pid_fils;
    int nb = 0;
    for (nb = 1; nb < 6; nb++)
    {
        do
        {
            pid_fils = fork();
        } while ((pid_fils == -1) && (errno == EAGAIN));
        if (pid_fils == -1)
        {
            perror("fork");
        }
        else if (pid_fils == 0)
        {
            printf("Je suis bel et bien le fils numero %d\n", nb);
            break;
        }
        else
        {
            if (wait(NULL) == -1)
            {
                perror("wait :");
            }
        }
    }

    return EXIT_SUCCESS;
}