/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:46:35 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/28 21:37:26 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns -1 for a critical error, 0 if too many args, 1 if everything is ok
static int	check_cd(t_command *cmd)
{
	if (!cmd || !cmd->args)
		return (-1);
	if (cmd->args[1] && cmd->args[2])
		return (0);
	return (1);
}

char	*trim_useless_slashes(char *path)
{
	unsigned int	i;

	i = 0;
	while (path[i++])
		;
	if (--i != 0)
	{
		while (i > 1 && path[i] == '/')
			path[i] = 0;
	}
	return (path);
}

static int	exec_cd(t_command *cmd)
{
	char	*oldpwd;
	char	*cd_dir;
	int		flag;

	flag = 0;
	oldpwd = getcwd(0, 0);
	if (!cmd->args[1])
		cd_dir = get_env_val(cmd->env, "HOME");
	else
		cd_dir = trim_useless_slashes(cmd->args[1]);
	if (!chdir(cd_dir))
	{
		update_env(cmd->env, "PWD", getcwd(0, 0));
		update_env(cmd->env, "OLDPWD", oldpwd);
		if (flag)
			printf("%s\n", get_env_val(cmd->env, "PWD"));
		return (0);
	}
	if (cmd->args[1])
		printf("cd: no such file or directory: %s\n", cmd->args[1]);
	free(oldpwd);
	return (1);
}

unsigned int	_cd(t_command *cmd)
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
