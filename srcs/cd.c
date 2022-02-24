/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:46:35 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/24 17:28:16 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_last_path_dir(char *chdir_path)
{
	unsigned int	i;

	i = ft_strlen(chdir_path);
	while (chdir_path[--i] && chdir_path[--i] != '/')
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
	ft_memcpy(updated_path, chdir_path, cp_len);
	updated_path[cp_len] = '/';
	ft_memcpy(&updated_path[cp_len + 1], dir, dir_len);
	updated_path[cp_len + dir_len + 1] = 0;
	printf("updated path = %s\n", updated_path);
	free(chdir_path);
	return (updated_path);
}

void	cd(char **env, const char *path)
{
	char			**split;
	char			*chdir_path;
	unsigned int	i;

	(void)env;
	chdir_path = ft_strdup(get_env_val(env, "PWD"));
	printf("c_p = %s\n", chdir_path);
	split = ft_split2(path, '/');
	i = 0;
	while (split[i])
	{
		if (!ft_strncmp(split[i], "..", 2))
			chdir_path = del_last_path_dir(chdir_path);
		else
			chdir_path = add_to_path(chdir_path, split[i]);
		i++;
	}
	chdir(chdir_path);
}
