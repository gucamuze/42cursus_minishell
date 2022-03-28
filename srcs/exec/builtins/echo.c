/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:30:11 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/28 21:36:08 by gucamuze         ###   ########.fr       */
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
			printf("%s", cmd->args[i]);
			if (cmd->args[i + 1])
				printf(" ");
		}
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}