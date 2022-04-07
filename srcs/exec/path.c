/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:12:12 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/07 11:13:09 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_paths(const char *command, const char *paths, char **abs_p)
{
	char			**paths_split;
	unsigned int	i;

	paths_split = ft_split(paths, ':');
	i = -1;
	while (paths_split[++i])
	{
		*abs_p = ft_strjoin3(paths_split[i], "/", command);
		if (!access(*abs_p, F_OK))
		{
			free_split(paths_split);
			return (1);
		}
		free(*abs_p);
	}
	free_split(paths_split);
	return (-1);
}

int	get_absolute_path(const char *command, const char *paths, char **abs_p)
{
	if (!access(command, F_OK))
	{
		*abs_p = ft_strdup(command);
		return (1);
	}
	if (paths)
		return (try_paths(command, paths, abs_p));
	return (-1);
}
