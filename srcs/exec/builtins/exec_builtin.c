/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:46:16 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/29 18:42:03 by gucamuze         ###   ########.fr       */
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
	if (setup_output_redir(command) == -1)
		command->fds[1] = 1;
	printf("builtins fds => %d and %d\n", command->fds[0], command->fds[1]);
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
	if (command->fds[0] > 1)
		close(command->fds[0]);
	if (command->fds[1] > 1)
		close(command->fds[1]);
	return (g_exit);
}