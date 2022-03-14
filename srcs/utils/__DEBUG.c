/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __DEBUG.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:38:51 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/14 18:39:05 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__DEBUG_output_cmd_lst(t_command *cmd)
{
	printf("\ncommand => %s\n", cmd->command);
	for (size_t i = 0; cmd->args[i]; i++)
		printf("arg[%zu] => %s\n", i, cmd->args[i]);
	printf("end arg\n");
	if (cmd->next)
		__DEBUG_output_cmd_lst(cmd->next);
}

void	__DEBUG_output_split(char **split)
{
	for (size_t i = 0; split[i]; i++)
		printf("split[%zu] => %s\n", i, split[i]);
}