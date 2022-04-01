/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:30:11 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/01 15:09:10 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	is_valid_arg(char *str)
{
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str += 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

unsigned int	_echo(t_command *cmd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (cmd->args[i] && is_valid_arg(cmd->args[i]))
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