/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:46:35 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/25 00:02:26 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_last_path_dir(char *chdir_path)
{
	unsigned int	i;

	i = ft_strlen(chdir_path);
	while (chdir_path[--i] && chdir_path[i] != '/')
		chdir_path[i] = 0;
	chdir_path[i] = 0;
	return (chdir_path);
}

char	*add_to_path(char *chdir_path, char *dir)
{
	unsigned int	cp_len;
	unsigned int	dir_len;
	char			*updated_path;

	cp_len = ft_strlen(chdir_path);
	dir_len = ft_strlen(dir);
	updated_path = malloc(cp_len + dir_len + 2);
	if (!updated_path)
		return (0);
	updated_path = ft_strjoin3(chdir_path, "/", dir);
	return (updated_path);
}

int	cd(t_list *env, char *path)
{
	char			**split;
	char			*chdir_path;
	unsigned int	i;

	chdir_path = ft_strdup(get_env_val(env, "PWD"));
	split = ft_split(path, '/');
	if (!split)
		return(!printf("Error with split !\n"));
	i = 0;
	if (!chdir(path))
	{
		update_env(env, "PWD", getcwd(0, 0));
		return(0);
	}
	else
	{
		printf("cd: no such file or directory: %s\n", path);
		return(1);
	}
	
}
