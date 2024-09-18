/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:11:54 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/18 14:55:42 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_and_exit(t_pipex *pipex, char *message)
{
	int	exit_status;

	free_command_list(pipex);
	exit_status = EXIT_SUCCESS;
	if (message)
	{
		ft_putstr_fd(message, 2);
		exit_status = EXIT_FAILURE;
	}
	exit(exit_status);
}

int	main(int argc, char **argv)
{
	t_pipex	*pipex;
	int		input_fd;
	int		output_fd;

	if (argc < 5)
		return (ft_putstr_fd("Error: Not enough arguments\n", 2), 1);
	input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1)
		return (perror("Error opening input file"), 1);
	output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		return (perror("Error opening output file"), close(input_fd), 1);
	pipex = parse_commands(argc, argv);
	if (!pipex)
		return (ft_putstr_fd("Error: Failed to parse commands\n", 2),
			close(input_fd), close(output_fd), 1);
	if (execute_pipeline(pipex, input_fd, output_fd) != 0)
		ft_putstr_fd("Error: Pipeline execution failed\n", 2);
	free_command_list(pipex);
	close(input_fd);
	close(output_fd);
	return (0);
}
