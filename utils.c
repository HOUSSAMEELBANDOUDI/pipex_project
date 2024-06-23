#include "pipex.h"

void pipex(int f1, int f2, char **av, char **envp)
{
    int     pipefd[2];
    pid_t   child1;
    pid_t   child2;

    if (pipe(pipefd) == -1)
    {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }
    child1 = fork();
    if (child1 == -1)
    {
        perror("child1 failed");
        exit(EXIT_FAILURE);
    }
    if (child1 == 0)
        child_one(f1, pipefd, av[2], envp);
     child2 = fork();
    if (child2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child2 == 0)
        child_two(f2, pipefd, av[3], envp);

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);
}

void child_one(int f1, int pipefd[], char *cmd1, char **envp)
{
    close(pipefd[0]); // Close unused read end of the pipe
    dup2(f1, STDIN_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    close(f1);
    parsing (cmd1, envp);
}

void child_two(int f2, int pipefd[], char *cmd2, char **envp)
{
    // Child process for cmd2
    close(pipefd[1]); // Close unused write end of the pipe
    dup2(pipefd[0], STDIN_FILENO);
    dup2(f2, STDOUT_FILENO);
    close(pipefd[0]);
    close(f2);
    parsing(cmd2, envp);
}
