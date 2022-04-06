/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:46:16 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 16:58:12 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	is_builtin(const char *command)
{
	if (!ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "exit"))
		return (1);
	return (0);
}

// mode 0 for standalone, mode 1 for forked
int	exec_builtin(t_command *cmd, int mode)
{
	if (!mode)
		if (pipe(cmd->fds) == -1 || !setup_input_redir(cmd)
			|| !setup_output_redir(cmd))
			return (-1);
	if (!ft_strcmp(cmd->command, "cd"))
		cmd->exit_code = _cd(cmd);
	else if (!ft_strcmp(cmd->command, "pwd"))
		cmd->exit_code = _pwd(cmd);
	else if (!ft_strcmp(cmd->command, "env"))
		cmd->exit_code = _env(cmd);
	else if (!ft_strcmp(cmd->command, "unset"))
		cmd->exit_code = _unset(cmd);
	else if (!ft_strcmp(cmd->command, "export"))
		cmd->exit_code = _export(cmd);
	else if (!ft_strcmp(cmd->command, "echo"))
		cmd->exit_code = _echo(cmd);
	else if (!ft_strcmp(cmd->command, "exit"))
		;
	close(cmd->fds[1]);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (!cmd->next)
		close(cmd->fds[0]);
	if (mode)
		exit(cmd->exit_code);
	return (1);
}
