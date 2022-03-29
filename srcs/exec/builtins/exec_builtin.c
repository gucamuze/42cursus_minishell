/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:46:16 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/29 16:39:42 by gucamuze         ###   ########.fr       */
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

int	exec_builtin(t_command *command)
{
	setup_input_redir(command);
	setup_output_redir(command);
	if (!ft_strcmp(command->command, "cd"))
		g_exit = _cd(command);
	else if (!ft_strcmp(command->command, "pwd"))
		g_exit = _pwd(command);
	else if (!ft_strcmp(command->command, "env"))
		g_exit = _env(command);
	else if (!ft_strcmp(command->command, "unset"))
		g_exit = _unset(command);
	else if (!ft_strcmp(command->command, "export"))
		g_exit = _export(command);
	else if (!ft_strcmp(command->command, "echo"))
		g_exit = _echo(command);
	else if (!ft_strcmp(command->command, "exit"))
		;
	close(command->fds[0]);
	close(command->fds[1]);
	printf("closing fd %d..\n", command->fds[1]);
	return (g_exit);
}