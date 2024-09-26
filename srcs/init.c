/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:49:13 by genarogarib       #+#    #+#             */
/*   Updated: 2024/09/26 12:04:17 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	setup_heredoc(t_pipex *pipex, int argc, char **argv)
{
	pipex->limiter = argv[2];
	pipex->cmd_count = argc - 4;
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		error_exit(pipex, "Error opening output file");
}

static void	setup_files(t_pipex *pipex, int argc, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		ft_putendl_fd("Error opening input file", 2);
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex->cmd_count = argc - 3;
	if (pipex->outfile < 0)
		error_exit(pipex, "Error opening output file");
}

static void	setup_cmd_paths(t_pipex *pipex, char **envp)
{
	char	*path;

	path = find_path(envp);
	if (!path)
		error_exit(pipex, "Error: PATH not found in environment");
	pipex->cmd_paths = ft_split(path, ':');
	if (!pipex->cmd_paths)
		error_exit(pipex, "Error: Memory allocation failed for cmd_paths");
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->heredoc_mode = (argc > 1 && ft_strncmp(argv[1], "here_doc", 8) == 0);
	if (pipex->heredoc_mode)
		setup_heredoc(pipex, argc, argv);
	else
		setup_files(pipex, argc, argv);
	setup_cmd_paths(pipex, envp);
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->parent_pid = getpid();
	pipex->pipe = malloc(sizeof(int) * (pipex->cmd_count - 1) * 2);
	if (!pipex->pipe)
		error_exit(pipex, "Error: Memory allocation failed for pipe");
}
