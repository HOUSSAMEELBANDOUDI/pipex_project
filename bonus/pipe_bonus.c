#include "pipex_bonus.h"

void execute_command(char *cmd, char **envp) {
    parsing(cmd, envp);
}

void child_process(int infile, int outfile, char *cmd, char **envp) {
    if (dup2(infile, STDIN_FILENO) < 0 || dup2(outfile, STDOUT_FILENO) < 0) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(infile);
    close(outfile);
    execute_command(cmd, envp);
}

void pipex(int argc, char **argv, char **envp) {
    int pipes[2];
    int infile = open(argv[1], O_RDONLY);
    int outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    pid_t pid;
    int i = 2;
    int fd_in = infile;

    if (infile < 0 || outfile < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (i < argc - 2) {
        if (pipe(pipes) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            close(pipes[0]);
            child_process(fd_in, pipes[1], argv[i], envp);
        } else {
            close(pipes[1]);
            close(fd_in);
            fd_in = pipes[0];
            i++;
        }
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        child_process(fd_in, outfile, argv[i], envp);
    }

    close(fd_in);
    close(outfile);

    while (wait(NULL) > 0);
}

int main(int argc, char **argv, char **envp) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s file1 cmd1 cmd2 ... cmdn file2\n", argv[0]);
        return 1;
    }
    pipex(argc, argv, envp);
    return 0;
}
