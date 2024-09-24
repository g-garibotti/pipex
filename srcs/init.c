/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:49:13 by genarogarib       #+#    #+#             */
/*   Updated: 2024/09/24 17:03:59 by ggaribot         ###   ########.fr       */
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

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	char	*path;

	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		ft_putendl_fd("Error opening input file", 2);
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		error_exit(pipex, "Error opening output file");
	path = find_path(envp);
	if (!path)
		error_exit(pipex, "Error: PATH not found in environment");
	pipex->cmd_paths = ft_split(path, ':');
	if (!pipex->cmd_paths)
		error_exit(pipex, "Error: Memory allocation failed for cmd_paths");
	pipex->cmd_count = argc - 3;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->parent_pid = getpid();
	pipex->pipe = malloc(sizeof(int) * (pipex->cmd_count - 1) * 2);
	if (!pipex->pipe)
		error_exit(pipex, "Error: Memory allocation failed for pipe");
}
