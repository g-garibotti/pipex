/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:38:09 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/20 17:57:40 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main(int argc, char *argv[])  // Explicitly declare all three parameters
{
    ft_memset(&g_pipex, 0, sizeof(t_pipex));
    g_pipex.infile = -1;
    g_pipex.outfile = -1;
    g_pipex.pipe_fd[0] = -1;
    g_pipex.pipe_fd[1] = -1;

    if (argc < 5)
        cleanup_and_exit("Error: Invalid number of arguments");

    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        if (argc < 6)
            cleanup_and_exit("Error: Invalid number of arguments for here_doc");
        g_pipex.here_doc = 1;
        handle_heredoc(argv[2]);
        argv += 3;
        argc -= 3;
    }
    else
    {
        argv++;
        argc--;
    }

    parse_args(argc, argv);
    execute_commands(argv);

    cleanup_and_exit(NULL);
    return (0);
}