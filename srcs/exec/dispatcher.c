/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 01:09:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/08 02:26:51 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_and_set_errors(t_command *cmd)
{
	int			exit_code;
	t_command	*last;

	exit_code = -1;
	while (cmd)
	{
		if (!cmd->next)
			last = cmd;
		waitpid(cmd->pid, &exit_code, 0);
		if (WIFEXITED(exit_code))
			exit_code = WEXITSTATUS(exit_code);
		cmd = cmd->next;
	}
	if (g_exit != 130 << 8 && g_exit != 131 << 8)
	{
		if (last->exit_code == 127)
			g_exit = 127 << 8;
		else
			g_exit = exit_code << 8;
	}
}

static void	execute(t_command *cmd_lst, t_data *data)
{
	t_command	*cmd;

	cmd = cmd_lst;
	if (is_builtin(cmd_lst->command) && !cmd_lst->next)
	{
		exec_builtin(cmd_lst, 0, data);
		g_exit = cmd_lst->exit_code << 8;
	}
	else
	{
		while (cmd_lst && cmd_lst->command)
		{
			exec(cmd_lst, data);
			cmd_lst = cmd_lst->next;
		}
		wait_and_set_errors(cmd);
	}
}

static int	command_dispatcher(t_command *cmd_lst, t_data *data)
{
	if (cmd_lst)
	{
		if (cmd_lst->command)
			execute(cmd_lst, data);
		else
		{
			if (pipe(cmd_lst->fds) == -1)
				return (-1);
			if (!setup_input_redir(cmd_lst) || !setup_output_redir(cmd_lst))
				return (-1);
			command_dispatcher(cmd_lst->next, data);
		}
		set_signals(0);
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

int	parse_and_dispatch(t_env **env, char *user_input, t_data *data)
{
	t_list		*parsed_pipes;
	t_command	*cmd_lst;

	if (!check_unending_quotes(user_input))
		return (dispatcher_error(0, 0, 0));
	parsed_pipes = parse_pipes(user_input);
	if (!check_invalid_pipes(parsed_pipes))
		return (dispatcher_error(parsed_pipes, 0, 1));
	cmd_lst = cmd_lst_create(*env, parsed_pipes);
	if (!parse_redirects(cmd_lst))
		return (dispatcher_error(parsed_pipes, cmd_lst, 2));
	parse_commands(cmd_lst);
	parse_quotes(cmd_lst);
	set_fds(cmd_lst);
	data->env = env;
	data->user_input = user_input;
	data->first_cmd = cmd_lst;
	setup_heredocs(data, cmd_lst);
	command_dispatcher(cmd_lst, data);
	close_all_fds(cmd_lst);
	reassign_env(env, cmd_lst);
	cmd_lst_free(cmd_lst);
	set_signals(0);
	return (1);
}
