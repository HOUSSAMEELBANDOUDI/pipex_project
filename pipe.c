#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int f1;
    int f2;

    if (ac != 5)
        return (2);

    f1 = open(av[1], O_RDONLY);
    f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (f1 < 0 || f2 < 0)
    {
        perror("Error opening files");
        return (2);
    }
    pipex(f1, f2, av, envp);
    close(f1);
    close(f2);

    return EXIT_SUCCESS;
}
