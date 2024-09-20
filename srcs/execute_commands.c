/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:39:16 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/20 17:57:20 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* srcs/execute_commands.c */
#include "../includes/pipex.h"

static char *get_cmd_path(char *cmd)
{
    char **paths;
    char *path;
    char *part_path;
    int i;

    paths = ft_split(ft_getenv("PATH"), ':');
    if (!paths)
        cleanup_and_exit("PATH not found or memory allocation failed");
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK | X_OK) == 0)
        {
            g_pipex.cmd_paths = paths;
            return (path);
        }
        free(path);
        i++;
    }
    g_pipex.cmd_paths = paths;
    return (NULL);
}

static void execute_cmd(char *cmd)
{
    char **args;
    char *path;
    extern char **environ;

    args = ft_split(cmd, ' ');
    if (!args)
        cleanup_and_exit("Memory allocation failed");
    g_pipex.cmd_args = args;
    path = get_cmd_path(args[0]);
    if (!path)
        cleanup_and_exit("Command not found");
    if (execve(path, args, environ) == -1)
    {
        free(path);
        cleanup_and_exit("Error executing command");
    }
}

static void child_process(char *cmd)
{
    close(g_pipex.pipe_fd[0]);
    dup2(g_pipex.pipe_fd[1], STDOUT_FILENO);
    close(g_pipex.pipe_fd[1]);
    execute_cmd(cmd);
}

static void parent_process(void)
{
    close(g_pipex.pipe_fd[1]);
    dup2(g_pipex.pipe_fd[0], STDIN_FILENO);
    close(g_pipex.pipe_fd[0]);
}

void execute_commands(char **argv)
{
    int i;

    i = 1;
    while (i < g_pipex.cmd_count)
    {
        if (pipe(g_pipex.pipe_fd) == -1)
            cleanup_and_exit("Error creating pipe");

        g_pipex.pid = fork();
        if (g_pipex.pid == -1)
            cleanup_and_exit("Error forking process");

        if (g_pipex.pid == 0)
            child_process(argv[i]);
        else
        {
            parent_process();
            waitpid(g_pipex.pid, NULL, 0);
        }
        i++;
    }
    execute_cmd(argv[i]);
    cleanup_and_exit(NULL);  // Normal exit after all commands are executed
}