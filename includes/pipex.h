/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:18:52 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/20 17:56:43 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/libft.h"

/* Global variables */
typedef struct s_pipex
{
    int     infile;
    int     outfile;
    char    **cmd_paths;
    char    **cmd_args;
    char    **envp;  // Add this line
    pid_t   pid;
    int     pipe_fd[2];
    int     cmd_count;
    int     here_doc;
} t_pipex;

extern t_pipex g_pipex;

/* Function prototypes */
void    parse_args(int argc, char **argv);
void    execute_commands(char **argv);
void    handle_heredoc(char *limiter);
void    cleanup_and_exit(char *error_message);
char *ft_getenv(const char *name);

#endif