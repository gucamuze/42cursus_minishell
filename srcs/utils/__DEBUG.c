/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __DEBUG.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:38:51 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/26 20:10:15 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__DEBUG_output_cmd_lst(t_command *cmd)
{
	printf("command => %s\n", cmd->command);
	if (cmd->args)
		for (size_t i = 0; cmd->args[i]; i++)
			printf("arg[%zu] => {%s}\n", i, cmd->args[i]);
	if (cmd->redirects)
	{
		t_redirect *iterator = cmd->redirects;
		for (size_t i = 0; iterator; i++)
		{
			printf("redirect %zu => type %d, name {%s}\n", i, 
				iterator->redir_type, iterator->redir_name);
			iterator = iterator->next;
		}
	}
	if (cmd->next)
		__DEBUG_output_cmd_lst(cmd->next);
}

void	__DEBUG_output_split(char **split)
{
	for (size_t i = 0; split[i]; i++)
		printf("split[%zu] => {%s}\n", i, split[i]);
}