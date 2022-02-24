/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:46:35 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/24 19:20:19 by gucamuze         ###   ########.fr       */
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
	// if (path[ft_strlen(path) - 1] == '/') // to avoid segfault
	// 	path[ft_strlen(path) - 1] = 0;
	split = ft_split2(path, '/');
	if (!split)
		return(!printf("Error with split !\n"));
	printf("pre parsing cd => %s\n", chdir_path);
	i = 0;
	while (split[i])
	{
		if (!ft_strncmp(split[i], "..", 2))
			chdir_path = del_last_path_dir(chdir_path);
		else
			chdir_path = add_to_path(chdir_path, split[i]);
		i++;
	}
	printf("post parsing cd => %s\n", chdir_path);
	if (!chdir(chdir_path))
	{
		update_env(env, "PWD", chdir_path);
		return(0);
	}
	else
	{
		printf("cd: no such file or directory: %s\n", path);
		return(1);
	}
	
}
