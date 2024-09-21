/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genarogaribotti <genarogaribotti@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:38:09 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/21 14:35:56 by genarogarib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    if (argc < 5)
    {
        ft_putendl_fd("Error: Invalid number of arguments", 2);
        return (1);
    }
    ft_memset(&pipex, 0, sizeof(t_pipex));  // Initialize all members to 0/NULL
    init_pipex(&pipex, argc, argv, envp);
    pipex.argv = argv;
    pipex.parent_pid = getpid();
    pipex.pipe = malloc(sizeof(int) * (pipex.cmd_count - 1) * 2);
    if (!pipex.pipe)
    {
        ft_putendl_fd("Error: Memory allocation failed", 2);
        cleanup_pipex(&pipex);
        return (1);
    }

    execute_pipex(&pipex);
    cleanup_pipex(&pipex);
    return (0);
}
