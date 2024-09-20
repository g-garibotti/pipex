/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:46:34 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/20 17:46:42 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_pipex g_pipex;

static void close_fds(void)
{
    if (g_pipex.infile > 2)
        close(g_pipex.infile);
    if (g_pipex.outfile > 2)
        close(g_pipex.outfile);
    if (g_pipex.pipe_fd[0] > 2)
        close(g_pipex.pipe_fd[0]);
    if (g_pipex.pipe_fd[1] > 2)
        close(g_pipex.pipe_fd[1]);
}

static void free_memory(void)
{
    int i;

    if (g_pipex.cmd_paths)
    {
        i = 0;
        while (g_pipex.cmd_paths[i])
        {
            free(g_pipex.cmd_paths[i]);
            i++;
        }
        free(g_pipex.cmd_paths);
    }
    if (g_pipex.cmd_args)
    {
        i = 0;
        while (g_pipex.cmd_args[i])
        {
            free(g_pipex.cmd_args[i]);
            i++;
        }
        free(g_pipex.cmd_args);
    }
}

void cleanup_and_exit(char *error_message)
{
    if (error_message)
        ft_putendl_fd(error_message, 2);
    close_fds();
    free_memory();
    if (g_pipex.here_doc)
        unlink(".heredoc_tmp");
    exit(EXIT_FAILURE);
}