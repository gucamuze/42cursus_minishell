/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:30:56 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/24 18:53:38 by gucamuze         ###   ########.fr       */
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

void	update_env(t_list *env, char *var_name, char *value)
{
	while (ft_strncmp(env->content, var_name, ft_strlen(var_name)))
		env = env->next;
	free(env->content);
	env->content = ft_strjoin3(var_name, "=", value);
	free(value);
}

// Gets value of ENV variable given in argument. 
// Returns a pointer to it if found, NULL if not
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
