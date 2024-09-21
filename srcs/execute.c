/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genarogaribotti <genarogaribotti@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:56:09 by genarogarib       #+#    #+#             */
/*   Updated: 2024/09/21 14:34:11 by genarogarib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char *get_cmd(char **paths, char *cmd)
{
    char *tmp;
    char *command;

    while (*paths)
    {
        tmp = ft_strjoin(*paths, "/");
        command = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(command, 0) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

static void child_process(t_pipex pipex, char **argv, int i)
{
    pipex.cmd_args = ft_split(argv[i + 2], ' ');
    if (!pipex.cmd_args)
        error_exit(&pipex, "Error: Memory allocation failed for cmd_args");

    pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
    if (!pipex.cmd)
    {
        child_free(&pipex);
        error_exit(&pipex, "Command not found");
    }
    if (i == 0)
    {
        dup2(pipex.infile, STDIN_FILENO);
        dup2(pipex.pipe[1], STDOUT_FILENO);
    }
    else if (i == pipex.cmd_count - 1)
    {
        dup2(pipex.pipe[2 * i - 2], STDIN_FILENO);
        dup2(pipex.outfile, STDOUT_FILENO);
    }
    else
    {
        dup2(pipex.pipe[2 * i - 2], STDIN_FILENO);
        dup2(pipex.pipe[2 * i + 1], STDOUT_FILENO);
    }
    close_pipes(&pipex);
    execve(pipex.cmd, pipex.cmd_args, pipex.envp);
    error_exit(&pipex, "Error: Command execution failed");
}

void execute_pipex(t_pipex *pipex)
{
    int i;

    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        if (pipe(pipex->pipe + 2 * i) < 0)
            error_exit(pipex, "Error: Pipe creation failed");
        i++;
    }

    i = 0;
    while (i < pipex->cmd_count)
    {
        pipex->pid = fork();
        if (pipex->pid < 0)
            error_exit(pipex, "Error: Fork failed");
        if (pipex->pid == 0)
            child_process(*pipex, pipex->argv, i);
        i++;
    }
    close_pipes(pipex);
    waitpid(-1, NULL, 0);
}
