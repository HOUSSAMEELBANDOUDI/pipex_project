#include "pipex_bonus.h"

void here_doc(char *limiter) {
    char buffer[1024];
    int temp_file = open(".temp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ssize_t read_bytes;
    size_t limiter_len = ft_strlen(limiter);

    if (temp_file < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        write(STDOUT_FILENO, "> ", 2);
        read_bytes = read(STDIN_FILENO, buffer, 1024);
        if (read_bytes < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (read_bytes == 0) {
            break;
        }
        buffer[read_bytes] = '\0';
        if (ft_strncmp(buffer, limiter, limiter_len) == 0 && buffer[limiter_len] == '\n') {
            break;
        }
        write(temp_file, buffer, read_bytes);
    }

    close(temp_file);
}

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

void f ()
{
    system("lsof -c pipex");
}

void pipex(int argc, char **argv, char **envp) {
    atexit(f);
    int pipes[2];
    int infile, outfile;
    int i;
    int fd_in;
    pid_t pid;

    if (ft_strncmp(argv[1], "here_doc", 8) == 0) {
        here_doc(argv[2]);
        infile = open(".temp_heredoc", O_RDONLY);
        outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
        i = 3;
    } else {
        infile = open(argv[1], O_RDONLY);
        outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        i = 2;
    }

    if (infile < 0 || outfile < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_in = infile;

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

    while (waitpid(-1, NULL, 0) > 0);
}

int main(int argc, char **argv, char **envp) {
    if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6)) {
        fprintf(stderr, "Usage: %s [here_doc LIMITER] file1 cmd1 cmd2 ... cmdn file2\n", argv[0]);
        return EXIT_FAILURE;
    }
    pipex(argc, argv, envp);
    return EXIT_SUCCESS;
}