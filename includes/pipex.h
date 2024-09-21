/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genarogaribotti <genarogaribotti@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:18:52 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/21 14:35:27 by genarogarib      ###   ########.fr       */
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

typedef struct s_pipex
{
    int     infile;
    int     outfile;
    char    **cmd_paths;
    char    **cmd_args;
    char    *cmd;
    char    **argv;
    char    **envp;
    pid_t   pid;
    pid_t   parent_pid;
    int     *pipe;
    int     cmd_count;
} t_pipex;

/* Function prototypes */
void    init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void    execute_pipex(t_pipex *pipex);
void    cleanup_pipex(t_pipex *pipex);
void    close_pipes(t_pipex *pipex);
void    error_exit(t_pipex *pipex, char *error_message);
void    child_free(t_pipex *pipex);

#endif