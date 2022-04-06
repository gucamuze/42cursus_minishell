/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:34:08 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/06 17:50:34 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[0] == '-' || s[0] == '+')
			i++;
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

unsigned int	ft_exit(t_command *cmd, t_data *data, int mode)
{
	long long int	nb;

	if (mode == 0)
	{
		printf("exit");
		if (cmd->args[1] == NULL)
			g_exit = 0;
		else if (is_num(cmd->args[1]))
		{
			nb = ft_atoi(cmd->args[1]);
			if (nb >= 0 && nb <= 255)
				g_exit = nb;
			else if (nb >= -9223372036854775807 && nb <= 9223372036854775807)
				g_exit = nb % 256;
			else
			{
				g_exit = 2;
				printf(": %lld: numeric argument required", nb);
			}
		}
		cleanup(data->prompt, data->env);
		free(data->user);
		close_all_fds(cmd);
		cmd_lst_free(cmd);
		exit(g_exit);
	}
	return (0);
}
