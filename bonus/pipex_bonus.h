#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

typedef struct s_data
{
    char *path_from_envp;
    char **mypath;
    char **mycmdargs;
    char *cmd;
} t_data;

char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    **ft_split(char const *s, char c);
size_t  ft_strlen(const char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
void    *ft_calloc(size_t count, size_t size);
void    parsing(char *av, char **envp);
void    pipex(int argc, char **argv, char **envp);
void    child_process(int infile, int outfile, char *cmd, char **envp);
void    execute_command(char *cmd, char **envp);

#endif
