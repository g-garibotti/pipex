/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genarogaribotti <genarogaribotti@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:38:09 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/21 13:42:10 by genarogarib      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    if (argc < 5)
        error_exit(NULL, "Error: Invalid number of arguments");
    
    init_pipex(&pipex, argc, argv, envp);
    pipex.argv = argv;
    pipex.pipe = malloc(sizeof(int) * (pipex.cmd_count - 1) * 2);
    if (!pipex.pipe)
        error_exit(&pipex, "Error: Memory allocation failed");

    execute_pipex(&pipex);
    cleanup_pipex(&pipex);
    return (0);
}
