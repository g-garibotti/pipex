/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:38:54 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/20 17:47:14 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* srcs/parse_args.c */
#include "../includes/pipex.h"

void parse_args(int argc, char **argv)
{
    if (argc < 4)
        cleanup_and_exit("Invalid number of arguments");

    g_pipex.infile = open(argv[0], O_RDONLY);
    if (g_pipex.infile == -1)
        cleanup_and_exit("Error opening input file");

    g_pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (g_pipex.outfile == -1)
        cleanup_and_exit("Error opening output file");

    if (dup2(g_pipex.infile, STDIN_FILENO) == -1 || dup2(g_pipex.outfile, STDOUT_FILENO) == -1)
        cleanup_and_exit("Error duplicating file descriptors");

    g_pipex.cmd_count = argc - 2;
}