/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:37:30 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/26 11:45:46 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	write_heredoc(int tmp_fd, char *limiter)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, tmp_fd);
		free(line);
	}
}

void	handle_heredoc(t_pipex *pipex)
{
	int	tmp_fd;

	tmp_fd = open(HEREDOC_TMP, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd < 0)
		error_exit(pipex, "Failed to create temporary heredoc file");
	write_heredoc(tmp_fd, pipex->limiter);
	close(tmp_fd);
	pipex->infile = open(HEREDOC_TMP, O_RDONLY);
	if (pipex->infile < 0)
		error_exit(pipex, "Failed to open temporary heredoc file");
}
