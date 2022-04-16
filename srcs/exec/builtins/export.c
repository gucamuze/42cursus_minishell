/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:51:34 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/07 23:52:44 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Possible difference compared to the real export command :
// this version ignores input like "export =j", zsh and bash throw an error 
// beforehand and doesn't execute the export command
unsigned int	_export(t_command *cmd)
{
	char				*env_name;
	char				*env_value;
	unsigned int		i;

	i = 1;
	if (cmd->args[i] == NULL)
		return (_env(cmd));
	while (cmd->args[i])
	{
		env_name = get_env_name_from_string(cmd->args[i]);
		if (env_name)
		{
			env_value = ft_strdup(&cmd->args[i][ft_strlen(env_name) + 1]);
			if (get_env_val(cmd->env, env_name, 0) != NULL)
			{
				update_env(cmd->env, env_name, env_value);
				free(env_name);
			}
			else
				update_env(cmd->env, env_name, env_value);
		}
		i++;
	}
	return (0);
}
