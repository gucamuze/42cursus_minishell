/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:46:16 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/05 18:27:50 by malbrand         ###   ########.fr       */
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
			return (-1); // should close the pipe fd
	if (!ft_strcmp(cmd->command, "cd"))
		g_exit = _cd(cmd) << 8;
	else if (!ft_strcmp(cmd->command, "pwd"))
		g_exit = _pwd(cmd) << 8;
	else if (!ft_strcmp(cmd->command, "env"))
		g_exit = _env(cmd) << 8;
	else if (!ft_strcmp(cmd->command, "unset"))
		g_exit = _unset(cmd) << 8;
	else if (!ft_strcmp(cmd->command, "export"))
		g_exit = _export(cmd) << 8;
	else if (!ft_strcmp(cmd->command, "echo"))
		g_exit = _echo(cmd) << 8;
	else if (!ft_strcmp(cmd->command, "exit"))
		;
	close(cmd->fds[1]);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (!cmd->next)
		close(cmd->fds[0]);
	if (mode)
	{
		printf("exiting child with status %d\n", g_exit);
		exit(g_exit);
	}
	return (0);
}
