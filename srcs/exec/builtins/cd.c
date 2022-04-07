/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:46:35 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/07 20:39:33 by malbrand         ###   ########.fr       */
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

static int	update_pwds(t_command *cmd, char *pwd, char *oldpwd)
{
	if (!get_env_val(cmd->env, "PWD", 0))
		update_env(cmd->env, ft_strdup("PWD"), pwd);
	else
		update_env(cmd->env, "PWD", pwd);
	if (!oldpwd)
		oldpwd = ft_strdup(pwd);
	if (!get_env_val(cmd->env, "OLDPWD", 0))
		update_env(cmd->env, ft_strdup("OLDPWD"), oldpwd);
	else
		update_env(cmd->env, "OLDPWD", oldpwd);
	return (0);
}

static int	exec_cd(t_command *cmd)
{
	char	*oldpwd;
	char	*cd_dir;

	oldpwd = get_env_val(cmd->env, "PWD", 1);
	if (!cmd->args[1])
	{
		cd_dir = get_env_val(cmd->env, "HOME", 0);
		if (!cd_dir)
		{
			free(oldpwd);
			return (_exit_err(" HOME not set", cmd, 1, 1));
		}
	}
	else
		cd_dir = trim_useless_slashes(cmd->args[1]);
	if (!chdir(cd_dir))
		return (update_pwds(cmd, getcwd(0, 0), oldpwd));
	else
	{
		free(oldpwd);
		return (_error(cmd->args[1], 1));
	}
	if (cmd->args[1])
	{
		ft_putstr_fd("cd: no such file or directory: ", cmd->fds[1]);
		ft_putendl_fd(cmd->args[1], cmd->fds[1]);
	}
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
		{
			ft_putstr_fd("cd: too many arguments\n", cmd->fds[1]);
			return (1);
		}
		return (0);
	}
	return (exec_cd(cmd));
}
