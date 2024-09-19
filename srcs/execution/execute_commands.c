/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:52:42 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/19 16:53:01 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
function	execute_pipeline(pipex, input_fd, output_fd)
	for each command in pipex
		create pipe
		fork process
		if child process
			set up input/output redirection
			execute command
		else
			wait for child process
	return success/failure status
*/