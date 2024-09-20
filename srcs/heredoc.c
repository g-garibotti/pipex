/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:40:06 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/20 17:47:22 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* srcs/heredoc.c */
#include "../includes/pipex.h"

void handle_heredoc(char *limiter)
{
    char *line;
    int fd;

    fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        cleanup_and_exit("Error creating heredoc temporary file");

    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(0);
        if (!line)
            break;
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 &&
            line[ft_strlen(limiter)] == '\n')
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd);
        free(line);
    }
    close(fd);

    g_pipex.infile = open(".heredoc_tmp", O_RDONLY);
    if (g_pipex.infile == -1)
        cleanup_and_exit("Error opening heredoc temporary file");
    if (dup2(g_pipex.infile, STDIN_FILENO) == -1)
        cleanup_and_exit("Error duplicating heredoc file descriptor");
}