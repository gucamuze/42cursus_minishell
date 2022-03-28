/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:54:37 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/28 19:02:26 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	_env(t_command *cmd)
{
	if (!cmd->args[1])
	{
		print_env(cmd->env);
		exit(0);
	}
	exit(127);
}