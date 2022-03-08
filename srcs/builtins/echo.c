/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:30:11 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/08 15:51:58 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	_echo(t_command *cmd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 0;
	while (cmd->args[i] && !ft_strncmp(cmd->args[i], "-n", 2))
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i++]);
		if (cmd->args[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (0);
}