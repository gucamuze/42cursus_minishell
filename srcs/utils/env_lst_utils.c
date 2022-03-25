/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 04:39:56 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/25 15:00:51 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*envlst_last(t_env *lst)
{
	t_env	*last;

	last = NULL;
	if (lst)
	{
		last = lst;
		while (last->next)
			last = last->next;
	}
	return (last);
}

size_t	envlst_size(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

t_env	*envlst_new(char *var_name, char *var_value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = var_name;
	new->value = var_value;
	new->next = NULL;
	return (new);
}

void	envlst_add_back(t_env **env, t_env *new)
{
	t_env	*last;
	
	if (*env)
	{
		last = envlst_last(*env);
		last->next = new;
	}
	else
		*env = new;
}