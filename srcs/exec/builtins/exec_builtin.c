/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:46:16 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/30 17:44:01 by gucamuze         ###   ########.fr       */
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

int	exec_builtin(t_command *cmd)
{
	// printf("builtins fds => %d, %d\n", cmd->fds[0], cmd->fds[1]);
	if (!ft_strcmp(cmd->command, "cd"))
		g_exit = _cd(cmd);
	else if (!ft_strcmp(cmd->command, "pwd"))
		g_exit = _pwd(cmd);
	else if (!ft_strcmp(cmd->command, "env"))
		g_exit = _env(cmd);
	else if (!ft_strcmp(cmd->command, "unset"))
		g_exit = _unset(cmd);
	else if (!ft_strcmp(cmd->command, "export"))
		g_exit = _export(cmd);
	else if (!ft_strcmp(cmd->command, "echo"))
		g_exit = _echo(cmd);
	else if (!ft_strcmp(cmd->command, "exit"))
		;
	close(cmd->fds[1]);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (!cmd->next)
		close(cmd->fds[0]);
	return (g_exit);
}