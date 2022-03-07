/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:47:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/07 17:38:04 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_command *cmd)
{
	if (!cmd->args[0])
	{
		printf("pwd => %s\n", get_env_val(cmd->env, "PWD"));
		return (0);
	}
	else
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
}