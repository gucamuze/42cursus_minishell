/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:46:35 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/07 17:38:12 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns -1 for a critical error, 0 if too many args, 1 if everything is ok
static int	check_cd(t_command *cmd)
{
	if (!cmd || !cmd->args)
		return (-1);
	if (!cmd->args[0])
		cmd->args[0] = get_env_val(cmd->env, "HOME");
	else if (cmd->args[1])
		return (0);
	return (1);
}

static int	exec_cd(t_command *cmd)
{
	char	*oldpwd;
	int		flag;

	flag = 0;
	oldpwd = getcwd(0, 0);
	if (!chdir(cmd->args[0]))
	{
		update_env(cmd->env, "PWD", getcwd(0, 0));
		update_env(cmd->env, "OLDPWD", oldpwd);
		if (flag)
			printf("%s\n", get_env_val(cmd->env, "PWD"));
		return (0);
	}
	if (cmd->args[0])
		printf("cd: no such file or directory: %s\n", cmd->args[0]);
	free(oldpwd);
	return (1);
}

int	cd(t_command *cmd)
{
	int		chk_ret;

	chk_ret = check_cd(cmd);
	if (chk_ret < 1)
	{
		if (chk_ret == 0)
			printf("cd: too many arguments\n");
		return (0);
	}
	return (exec_cd(cmd));
}
