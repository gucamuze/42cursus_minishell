/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:30:56 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 22:55:42 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name_from_string(char *str)
{
	char			*env_name;
	unsigned int	i;

	i = 0;
	env_name = NULL;
	while (str[i])
	{
		if (str[i] == '=')
		{
			env_name = malloc(i + 1);
			if (env_name)
			{
				ft_memcpy(env_name, str, i);
				env_name[i] = 0;
			}
			break ;
		}
		i++;
	}
	return (env_name);
}

char	**envlst_to_tab(t_env *env)
{
	char	**tab;
	size_t	size;
	size_t	i;

	size = envlst_size(env);
	tab = malloc((size + 1) * sizeof(char *));
	if (!tab)
		return (0);
	i = 0;
	while (i < size)
	{
		tab[i++] = ft_strjoin3(env->name, "=", env->value);
		env = env->next;
	}
	tab[i] = 0;
	return (tab);
}

t_env	*env_to_lst(char **env)
{
	t_env	*lst;
	char	*var_name;
	char	*var_value;

	lst = NULL;
	if (*env)
	{
		while (*env)
		{
			var_name = get_env_name_from_string(*env);
			var_value = ft_strdup(&(*env)[ft_strlen(var_name) + 1]);
			envlst_add_back(&lst, envlst_new(var_name, var_value));
			env++;
		}
	}
	else
	{
		envlst_add_back(&lst, envlst_new(ft_strdup("PWD"), getcwd(0, 0)));
		envlst_add_back(&lst, envlst_new(ft_strdup("SHLVL"), ft_strdup("0")));
		envlst_add_back(&lst, envlst_new(ft_strdup("PATH"), ft_strdup(D_PATH)));
	}
	return (lst);
}

void	print_env(t_env *env, int fd)
{
	if (env)
	{
		ft_putstr_fd(env->name, fd);
		write(fd, "=", 1);
		ft_putstr_fd(env->value, fd);
		write(fd, "\n", 1);
		print_env(env->next, fd);
	}
}
