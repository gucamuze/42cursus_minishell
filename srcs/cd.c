/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:46:35 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/02 22:51:46 by gucamuze         ###   ########.fr       */
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
	char	*oldpwd;

	oldpwd = getcwd(0, 0);
	if (!path)
		path = get_env_val(env, "HOME");
	if (!ft_strncmp(path, "-", 1))
		path = get_env_val(env, "OLDPWD");
	if (!chdir(path))
	{
		update_env(env, "PWD", getcwd(0, 0));
		update_env(env, "OLDPWD", oldpwd);
		return(0);
	}
	printf("cd: no such file or directory: %s\n", path);
	free(oldpwd);
	return(1);
}
