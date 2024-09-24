/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:12:51 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/24 17:13:10 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	write_to_pipe(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void	handle_heredoc(t_pipex *pipex, char *limiter)
{
	int	heredoc_pipe[2];

	if (pipe(heredoc_pipe) < 0)
		error_exit(pipex, "Error: Heredoc pipe creation failed");
	write_to_pipe(heredoc_pipe[1], limiter);
	close(heredoc_pipe[1]);
	pipex->infile = heredoc_pipe[0];
	pipex->is_heredoc = 1;
}
