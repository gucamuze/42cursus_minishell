/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:51:26 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/28 21:36:33 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_exec(t_command *cmd, t_env *iterator, int i)
{
	t_env	*prev;

	prev = 0;
	while (iterator)
	{
		if (!ft_strncmp(cmd->args[i], iterator->name, ft_strlen(cmd->args[i])))
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
	t_env	*iterator;
	int		i;

	if (!cmd->args[1])
	{
		printf("unset: not enough arguments\n");
		exit(1);
	}
	i = 0;
	while (cmd->args[++i])
	{
		iterator = cmd->env;
		unset_exec(cmd, iterator, i);
	}
	return (0);
}