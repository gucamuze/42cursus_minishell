/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:45:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/03 03:39:36 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("MAIN SIGINT\n");
		g_exit = 130 << 8;
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	exec_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("EXEC SIGINT\n");
		g_exit = 130 << 8;
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		g_exit = 131 << 8;
		exit(131);
	}
}

// Mode 0 for main sequence, 1 for execution mode
void	set_signals(int mode)
{
	if (!mode)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &main_handler);
	}
	else
	{
		// sa.sa_handler = &exec_handler;
		signal(SIGQUIT, &exec_handler);
		signal(SIGINT, &exec_handler);
	}
}
