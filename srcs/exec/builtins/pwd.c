/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:47:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/28 19:03:15 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	_pwd(t_command *cmd)
{
	if (!cmd->args[1])
	{
		printf("pwd => %s\n", get_env_val(cmd->env, "PWD"));
		exit(0);
	}
	else
	{
		printf("pwd: too many arguments\n");
		exit(1);
	}
}