/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:24:53 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/08 18:04:27 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cmd_free(t_command *cmd)
{
	if (cmd)
	{
		if (cmd->args)
			free_split(cmd->args);
		if (cmd->next)
			cmd_free(cmd->next);
		free(cmd);
	}
}

t_command	*cmd_create(t_env *env, char *user_input)
{
	t_command	*cmd;
	size_t		i;
	
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (0);
	i = 0;
	/** NEED TO REPLACE THIS SPLIT BY A REAL PARSER !! **/
	cmd->args = create_args(env, user_input);
	/** ^this one **/
	if (cmd->args)
		cmd->command = cmd->args[0];
	else
		cmd->command = 0;
	cmd->env = env;
	cmd->token = 0;
	cmd->next = 0;
	return (cmd);
}

void	__DEBUG_output_cmd(t_command *cmd)
{
	printf("command => %s\n", cmd->command);
	for (size_t i = 0; cmd->args[i]; i++)
		printf("arg[%zu] => %s\n", i, cmd->args[i]);
	printf("token => %d\n", cmd->token);
	if (cmd->next)
		__DEBUG_output_cmd(cmd->next);
}

void	__DEBUG_output_split(char **split)
{
	for (size_t i = 0; split[i]; i++)
		printf("split[%zu] => %s\n", i, split[i]);
}