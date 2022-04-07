/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:45:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/07 04:13:46 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130 << 8;
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	child_handler(int sig)
{
	if (sig == SIGINT)
		exit(130);
	else if (sig == SIGQUIT)
		exit(131);
}

static void	parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exit = 130 << 8;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		g_exit = 131 << 8;
	}
}

// Mode 0 for main sequence, 1 for exec child, 2 for exec parent, 3 for heredoc
void	set_signals(int mode)
{
	if (mode == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &main_handler);
	}
	else if (mode == 1 || mode == 3)
	{
		signal(SIGQUIT, &child_handler);
		signal(SIGINT, &child_handler);
	}
	else if (mode == 2)
	{
		signal(SIGQUIT, &parent_handler);
		signal(SIGINT, &parent_handler);
	}
}
