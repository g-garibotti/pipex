/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:56:29 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/20 17:56:44 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char *ft_getenv(const char *name)
{
    extern char **environ;
    int i;
    size_t len;

    len = ft_strlen(name);
    i = 0;
    while (environ[i])
    {
        if (ft_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
            return (&environ[i][len + 1]);
        i++;
    }
    return (NULL);
}