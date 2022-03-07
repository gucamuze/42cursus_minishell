/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:46:35 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/03 04:52:58 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// LEGACY CODE

// char	*del_last_path_dir(char *chdir_path)
// {
// 	unsigned int	i;

// 	i = ft_strlen(chdir_path);
// 	while (chdir_path[--i] && chdir_path[i] != '/')
// 		chdir_path[i] = 0;
// 	chdir_path[i] = 0;
// 	return (chdir_path);
// }

// char	*add_to_path(char *chdir_path, char *dir)
// {
// 	unsigned int	cp_len;
// 	unsigned int	dir_len;
// 	char			*updated_path;

// 	cp_len = ft_strlen(chdir_path);
// 	dir_len = ft_strlen(dir);
// 	updated_path = malloc(cp_len + dir_len + 2);
// 	if (!updated_path)
// 		return (0);
// 	updated_path = ft_strjoin3(chdir_path, "/", dir);
// 	return (updated_path);
// }

// LEGACY CODE OFF

int	cd(t_env *env, char *path)
{
	char	*oldpwd;
	int		flag;

	oldpwd = getcwd(0, 0);
	flag = 0;
	if (!path)
		path = get_env_val(env, "HOME");
	if (!ft_strncmp(path, "-", 1))
	{
		path = get_env_val(env, "OLDPWD");
		flag = 1;
	}
	if (!chdir(path))
	{
		update_env(env, "PWD", getcwd(0, 0));
		update_env(env, "OLDPWD", oldpwd);
		if (flag)
			printf("%s\n", get_env_val(env, "PWD"));
		return (0);
	}
	if (path)
		printf("cd: no such file or directory: %s\n", path);
	else
		printf("cd: no such file or directory:\n");
	free(oldpwd);
	return (1);
}
