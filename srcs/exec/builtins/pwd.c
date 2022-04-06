/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:47:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 16:58:28 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	_pwd(t_command *cmd)
{
	if (!cmd->args[1])
	{
		ft_putstr_fd("pwd => ", cmd->fds[1]);
		ft_putendl_fd(get_env_val(cmd->env, "PWD", 0), cmd->fds[1]);
		return (0);
	}
	else
	{
		ft_putstr_fd("pwd: too many arguments\n", cmd->fds[1]);
		return (1);
	}
}
