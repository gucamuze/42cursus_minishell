/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:04:28 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/16 00:13:55 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_execbuiltin(t_command	*cmd_lst)
{
	
	if (ft_strcmp(cmd_lst->command, "cd") == 0)
		_cd(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "pwd") == 0)
		_pwd(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "env") == 0)
		_env(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "unset") == 0)
		_unset(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "export") == 0)
		_export(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "echo") == 0)
		_echo(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "exit") == 0)
		exit(1);
	exit(0);
}

int	havebuiltin(t_command	*cmd_lst)
{
	if (ft_strcmp(cmd_lst->command, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "exit") == 0)
		return (1); // exit
	return (0);
}

void	exec_cmd(t_command *cmd, char **env, t_env *envt)
{
	char *str;
	
	if (havebuiltin(cmd))
	{
		// printf("exec\n");
		ft_execbuiltin(cmd);
	}
	str = get_absolute_path(cmd->args, envt);
	cmd->args[0] = str;
	if (execve(str, cmd->args, env) == -1)
	{
		// printf("!execve\n");
		perror("shell");
		exit(1);
	}
}