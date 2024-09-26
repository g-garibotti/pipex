/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:56:09 by genarogarib       #+#    #+#             */
/*   Updated: 2024/09/26 12:01:04 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			error_exit(pipex, "Error: Pipe creation failed");
		i++;
	}
}

static void	fork_processes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->pid = fork();
		if (pipex->pid < 0)
			error_exit(pipex, "Error: Fork failed");
		if (pipex->pid == 0)
			child_process(pipex, i);
		i++;
	}
}

static void	wait_for_children(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}

void	execute_pipex(t_pipex *pipex)
{
	if (pipex->heredoc_mode)
		handle_heredoc(pipex);
	create_pipes(pipex);
	fork_processes(pipex);
	close_pipes(pipex);
	wait_for_children(pipex);
}
