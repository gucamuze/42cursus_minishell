/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:45:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/03 01:16:27 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_handler(int sig)
{
	if (sig == SIGKILL)
		printf("SIGKILL\n");
	if (sig == SIGINT)
	{
		g_exit = 130 << 8;
		exit (130);
	}
	else if (sig == SIGQUIT)
		;
}

void	exec_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("exec SIGINT signal received (TEMPORARY: quitting...)\n");
		exit(0);
	}
	else if (sig == SIGQUIT)
		printf("exec SIGQUIT signal received (TEMPORARY: quitting...\n");
}

// Mode 0 for main sequence, 1 for execution mode
void	set_sigaction(struct sigaction *sa, int mode)
{
	// sa->sa_mask = 0;
	// sa->sa_flags = 0;
	// sa->sa_mask = sigemptyset(0);
	if (!mode)
		sa->sa_handler = &main_handler;
	else
		sa->sa_handler = &exec_handler;
	sigaction(SIGINT, sa, 0);
	sigaction(SIGQUIT, sa, 0);
	sigaction(SIGKILL, sa, 0);
}
