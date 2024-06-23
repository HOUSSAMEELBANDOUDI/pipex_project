#include "pipex.h"

void parsing (char *av, char **envp)
{
    char *path_from_envp;
    char **mypath;
    char **mycmdargs;
    int i;
    char *cmd;

    i = 0;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_from_envp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
            break;
        }
        i++;
    }
    mypath = ft_split(path_from_envp, ':');
    mycmdargs = ft_split(av, ' ');
    i = 0;
    while (mypath[i])
    {
        cmd = ft_strjoin(mypath[i], "/");
        cmd = ft_strjoin(cmd, mycmdargs[0]);
        if (access(cmd, X_OK) == 0)
        {
            execve(cmd, mycmdargs, envp);
            perror("execve");
        }
        free(cmd);
        i++;
    }

    exit (EXIT_FAILURE);
}



