/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:51:26 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/03 02:58:57 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	unset_exec(t_command *cmd, t_env *iterator, int i)
// {
// 	t_env	*prev;

// 	prev = 0;
// 	while (iterator)
// 	{
// 		if (!ft_strncmp(cmd->args[i], iterator->name, ft_strlen(cmd->args[i]))
// 			&& ft_strlen(cmd->args[i]) == ft_strlen(iterator->name))
// 		{
// 			if (!prev)
// 				cmd->env = iterator->next;
// 			else
// 				prev->next = iterator->next;
// 			free(iterator->name);
// 			free(iterator->value);
// 			free(iterator);
// 			break ;			
// 		}
// 		prev = iterator;
// 		iterator = iterator->next;
// 	}
// }

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