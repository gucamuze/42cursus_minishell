/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:34:08 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/07 04:53:00 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(const char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static unsigned long long int	ft_atoul(const char *nptr)
{
	int							sign;
	unsigned long long int		result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr++ - 48);
	}
	return (sign * result);
}

unsigned int	ft_exit(t_command *cmd, t_data *data, int mode)
{
	long long int			l_nb;
	unsigned long long int	nb;

	if (mode == 0)
	{
		printf("exit");
		if (cmd->args[1] == NULL)
			g_exit = 0;
		else if (is_num(cmd->args[1]))
		{
			if (cmd->args[2] != NULL)
			{
				printf(": too many arguments\n");
				return (1);
			}
			if (cmd->args[1][0] != '-')
			{
				nb = ft_atoul(cmd->args[1]);
				if (nb <= 255)
					g_exit = nb;
				else if (nb <= 9223372036854775807)
					g_exit = nb % 256;
				else
				{
					g_exit = 2;
					printf(": %s: numeric argument required", cmd->args[1]);
				}
			}
			else if (cmd->args[1][0] == '-')
			{
				l_nb = ft_atol(cmd->args[1]);
				printf("\n%lld\n\n", l_nb);
				if (l_nb < 0)
					g_exit = l_nb % 256;
				else
				{
					g_exit = 2;
					printf(": %s: numeric argument required", cmd->args[1]);
				}
			}
		}
		else
		{
			printf(": %s: numeric argument required", cmd->args[1]);
			g_exit = 2;
		}
		printf("\n");
		cleanup(data);
		close_all_fds(cmd);
		cmd_lst_free(cmd);
		exit(g_exit);
	}
	return (0);
}
