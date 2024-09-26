/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:00:35 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/26 12:00:47 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	redirect_io(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipe[1], STDOUT_FILENO);
	}
	else if (i == pipex->cmd_count - 1)
	{
		dup2(pipex->pipe[2 * i - 2], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->pipe[2 * i - 2], STDIN_FILENO);
		dup2(pipex->pipe[2 * i + 1], STDOUT_FILENO);
	}
}

static void	close_unused_fds(t_pipex *pipex, int i)
{
	int	j;

	j = 0;
	while (j < (pipex->cmd_count - 1) * 2)
	{
		if ((i == 0 && j != 1) || (i == pipex->cmd_count - 1 && j != 2 * i - 2)
			|| (i != 0 && i != pipex->cmd_count - 1 && j != 2 * i - 2 && j != 2
				* i + 1))
			close(pipex->pipe[j]);
		j++;
	}
	if (i != 0 && pipex->infile > 0)
		close(pipex->infile);
	if (i != pipex->cmd_count - 1 && pipex->outfile > 0)
		close(pipex->outfile);
}

static void	setup_command(t_pipex *pipex, int i)
{
	int	cmd_index;

	cmd_index = i + 2;
	if (pipex->heredoc_mode)
		cmd_index++;
	pipex->cmd_args = ft_split(pipex->argv[cmd_index], ' ');
	if (!pipex->cmd_args)
		error_exit(pipex, "Error: Memory allocation failed for cmd_args");
	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		cleanup_pipex(pipex);
		error_exit(pipex, "Command not found");
	}
}

void	child_process(t_pipex *pipex, int i)
{
	setup_command(pipex, i);
	close_unused_fds(pipex, i);
	if (i == 0 && pipex->infile < 0)
	{
		cleanup_pipex(pipex);
		exit(1);
	}
	redirect_io(pipex, i);
	execve(pipex->cmd, pipex->cmd_args, pipex->envp);
	cleanup_pipex(pipex);
	error_exit(pipex, "Error: Command execution failed");
}
