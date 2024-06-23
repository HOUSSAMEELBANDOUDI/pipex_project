#include "pipex_bonus.h"

void parsing(char *cmd, char **envp) {
    t_data data;
    int i = 0;

    while (envp[i]) {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0) {
            data.path_from_envp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
            break;
        }
        i++;
    }

    data.mypath = ft_split(data.path_from_envp, ':');
    data.mycmdargs = ft_split(cmd, ' ');

    i = 0;
    while (data.mypath[i]) {
        data.cmd = ft_strjoin(data.mypath[i], "/");
        char *temp = data.cmd;
        data.cmd = ft_strjoin(data.cmd, data.mycmdargs[0]);
        free(temp);

        if (access(data.cmd, X_OK) == 0) {
            execve(data.cmd, data.mycmdargs, envp);
            perror("execve");
        }

        free(data.cmd);
        i++;
    }

    fprintf(stderr, "Command not found: %s\n", cmd);
    exit(EXIT_FAILURE);
}
