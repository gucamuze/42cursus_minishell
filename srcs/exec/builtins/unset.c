/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:51:26 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 16:57:49 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_exec(t_command *cmd, char *var_name)
{
	t_env	*prev;
	t_env	*iterator;

	prev = 0;
	iterator = cmd->env;
	while (iterator)
	{
		if (!ft_strcmp(iterator->name, var_name))
		{
			if (!prev)
				cmd->env = iterator->next;
			else
				prev->next = iterator->next;
			free(iterator->name);
			free(iterator->value);
			free(iterator);
			break ;
		}
		prev = iterator;
		iterator = iterator->next;
	}
}

unsigned int	_unset(t_command *cmd)
{
	int		i;

	if (!cmd->args[1])
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	i = 0;
	while (cmd->args[++i])
		unset_exec(cmd, cmd->args[i]);
	return (0);
}
