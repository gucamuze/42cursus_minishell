/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:30:56 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/24 23:48:34 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_to_lst(char **env)
{
	t_list	*lst;
	
	lst = NULL;
	if (env)
		while (*env)
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(*env++)));
	return (lst);
}

void	unset(t_list **env, const char *var_name)
{
	t_list	*prev;

	prev = 0;
	while (*env)
	{
		if (!ft_strncmp(var_name, (*env)->content, ft_strlen(var_name)))
		{
			if (!prev)
				env = &(*env)->next;
			else
				prev->next = (*env)->next;
			free(*env);
			return ;			
		}
		prev = *env;
		*env = (*env)->next;
	}
}

void	print_env(t_list *env)
{
	if (env)
	{
		printf("%s\n", env->content);
		print_env(env->next);
	}
}

void	update_env(t_list *env, char *var_name, char *value)
{
	while (ft_strncmp(env->content, var_name, ft_strlen(var_name)))
		env = env->next;
	free(env->content);
	env->content = ft_strjoin3(var_name, "=", value);
	free(value);
}

// CAREFUL: The returned pointer is a pointer to the actual env var, no memory
// is allocated !!
char	*get_env_val(t_list *env, const char *var_name)
{
	size_t	var_len;

	var_len = ft_strlen(var_name);
	while (env)
	{
		if (ft_strnstr(env->content, var_name, var_len))
			return (env->content + var_len + 1);
		env = env->next;
	}
	return (NULL);
}
