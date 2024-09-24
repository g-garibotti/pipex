/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:38:09 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/24 17:14:59 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5 || argc > MAX_ARGS)
	{
		ft_putendl_fd("Error: Invalid number of arguments", 2);
		return (1);
	}
	ft_memset(&pipex, 0, sizeof(t_pipex));
	init_pipex(&pipex, argc, argv, envp);
	execute_pipex(&pipex);
	cleanup_pipex(&pipex);
	return (0);
}
