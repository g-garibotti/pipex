/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:49:42 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/19 17:01:43 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
function	parse_commands(argc, argv)
	create pipex structure
	for each command in argv (starting from argv[2] to argv[argc-2])
		parse command and its arguments
		add to pipex structure
	return pipex structure
*/

#include "pipex.h"

static t_pipex	*init_pipex(void)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->input_fd = -1;
	pipex->output_fd = -1;
	return (pipex);
}

static char	**split_command(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		return (NULL);
	return (args);
}

static void	free_pipex(t_pipex *pipex)
{
	t_pipex	*temp;

	while (pipex)
	{
		ft_free_split(pipex->args);
		temp = pipex->next;
		free(pipex);
		pipex = temp;
	}
}

t_pipex	*parse_commands(int argc, char **argv)
{
	t_pipex	*pipex;
	t_pipex	*current;
	int		i;

	pipex = init_pipex();
	if (!pipex)
		return (NULL);
	current = pipex;
	i = 2;
	while (i < argc - 1)
	{
		current->args = split_command(argv[i]);
		if (!current->args)
			return (free_pipex(pipex), NULL);
		if (i < argc - 2)
		{
			current->next = init_pipex();
			if (!current->next)
				return (free_pipex(pipex), NULL);
			current = current->next;
		}
		i++;
	}
	return (pipex);
}
