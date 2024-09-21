/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genarogaribotti <genarogaribotti@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:31:19 by genarogarib       #+#    #+#             */
/*   Updated: 2024/09/21 13:42:31 by genarogarib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void free_string_array(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void close_pipes(t_pipex *pipex)
{
    int i;

    i = 0;
    while (i < (pipex->cmd_count - 1) * 2)
    {
        close(pipex->pipe[i]);
        i++;
    }
}

void cleanup_pipex(t_pipex *pipex)
{
    if (pipex->infile > 0)
        close(pipex->infile);
    if (pipex->outfile > 0)
        close(pipex->outfile);
    
    close_pipes(pipex);
    
    free_string_array(pipex->cmd_paths);
    free_string_array(pipex->cmd_args);
    
    if (pipex->pipe)
        free(pipex->pipe);
    if (pipex->cmd)
        free(pipex->cmd);
}

void error_exit(t_pipex *pipex, char *error_message)
{
    if (error_message)
        ft_putendl_fd(error_message, 2);

    if (pipex)
        cleanup_pipex(pipex);

    exit(1);
}

void child_free(t_pipex *pipex)
{
    free_string_array(pipex->cmd_args);
    if (pipex->cmd)
        free(pipex->cmd);
}
