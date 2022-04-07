/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:54:40 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/07 20:59:18 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reassign_env(t_env **env, t_command *cmd)
{
	if (cmd->next)
	{
		while (cmd->next)
			cmd = cmd->next;
	}
	*env = cmd->env;
}

// !! var_name and value MUST BE malloc'd if value is 
// to be created and not updated !!
void	update_env(t_env *env, char *var_name, char *value)
{
	t_env	*iterator;

	iterator = env;
	while (iterator && ft_strcmp(iterator->name, var_name))
		iterator = iterator->next;
	if (iterator)
	{
		free(iterator->value);
		iterator->value = value;
	}
	else
		envlst_add_back(&env, envlst_new(var_name, value));
}

// if mode == 1, string will be dupped, else it's just a pointer
char	*get_env_val(t_env *env, const char *var_name, int mode)
{
	while (env)
	{
		if (!ft_strcmp(env->name, var_name))
		{
			if (mode)
				return (ft_strdup(env->value));
			return (env->value);
		}
		env = env->next;
	}
	return (0);
}
