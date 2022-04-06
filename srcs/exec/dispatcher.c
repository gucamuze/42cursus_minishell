/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 01:09:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 16:19:13 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_dispatcher(t_command *command, t_data *data)
{
	t_command	*cmd;
	
	cmd = command;
	if (command && command->command)
	{
		if (is_builtin(command->command) && !command->next)
			exec_builtin(command, 0, data);
		else
		{
			while (command && command->command)
			{
				exec(command, data);
				command = command->next;
			}
			while (cmd)
			{
				wait(&g_exit);
				cmd = cmd->next;
			}
		}
	}
	return (0);
}

static void	set_fds(t_command *cmd)
{
	if (cmd)
	{
		cmd->fds[0] = -1;
		cmd->fds[1] = -1;
		cmd->fd_in = -1;
		set_fds(cmd->next);
	}
}

static void	reassign_env(t_env **env, t_command *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	*env = cmd->env;
}

int	parse_and_dispatch(t_env **env, char *user_input, t_data *data)
{
	t_list		*parsed_pipes;
	t_command	*cmd_lst;

	if (!check_unending_quotes(user_input))
		return (!printf("Syntax error: invalid quotes !\n"));
	parsed_pipes = parse_pipes(user_input);
	if (!check_invalid_pipes(parsed_pipes))
		return (!printf("Syntax error: invalid pipe !\n"));
	cmd_lst = cmd_lst_create(*env, parsed_pipes);
	if (!parse_redirects(cmd_lst))
		return (!printf("Syntax error: invalid redirect !\n"));
	parse_commands(cmd_lst);
	parse_quotes(cmd_lst);
	set_fds(cmd_lst);
	__DEBUG_output_cmd_lst(cmd_lst);
	data->env = (*env);
	data->user = user_input;
	command_dispatcher(cmd_lst, data);
	close_all_fds(cmd_lst);
	reassign_env(env, cmd_lst);
	cmd_lst_free(cmd_lst);
	set_signals(0);
	return (1);
}
