/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:18:52 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/26 12:01:16 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_ARGS 1024
# define HEREDOC_TMP ".heredoc_tmp"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	char	**argv;
	char	**envp;
	pid_t	pid;
	pid_t	parent_pid;
	int		*pipe;
	int		cmd_count;
	int		heredoc_mode;
	char	*limiter;
}			t_pipex;

void		init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void		execute_pipex(t_pipex *pipex);
void		cleanup_pipex(t_pipex *pipex);
void		close_pipes(t_pipex *pipex);
void		error_exit(t_pipex *pipex, char *error_message);
void		free_string_array(char **arr);
char		*get_cmd(char **paths, char *cmd);
void		handle_heredoc(t_pipex *pipex);
void		child_process(t_pipex *pipex, int i);

#endif