/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:30:11 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/29 17:12:08 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	_echo(t_command *cmd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (cmd->args[i] && !ft_strncmp(cmd->args[i], "-n", 2))
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != 0)
		{
			ft_putstr_fd(cmd->args[i], cmd->fds[1]);
			if (cmd->args[i + 1])
				write(cmd->fds[1], " ", 1);
		}
		i++;
	}
	if (newline)
		write(cmd->fds[1], "\n", 1);
	return (0);
}