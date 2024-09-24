/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:31:19 by genarogarib       #+#    #+#             */
/*   Updated: 2024/09/24 17:03:53 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_pipex *pipex)
{
	int	i;

	if (!pipex->pipe)
		return ;
	i = 0;
	while (i < (pipex->cmd_count - 1) * 2)
	{
		close(pipex->pipe[i]);
		i++;
	}
}

void	cleanup_pipex(t_pipex *pipex)
{
	if (pipex->infile > 0)
		close(pipex->infile);
	if (pipex->outfile > 0)
		close(pipex->outfile);
	close_pipes(pipex);
	if (pipex->pipe)
		free(pipex->pipe);
	if (pipex->cmd_paths)
		free_string_array(pipex->cmd_paths);
	if (pipex->cmd_args)
		free_string_array(pipex->cmd_args);
	if (pipex->cmd)
		free(pipex->cmd);
}

void	error_exit(t_pipex *pipex, char *error_message)
{
	if (error_message)
		ft_putendl_fd(error_message, 2);
	if (pipex && getpid() == pipex->parent_pid)
		cleanup_pipex(pipex);
	exit(1);
}
