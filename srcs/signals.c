/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:45:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/26 17:04:07 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == 2)
	{
		printf("SIGINT signal received (TEMPORARY: quitting...)\n");
		exit(0);
	}
	else if (sig == 3)
		printf("SIGQUIT signal received (TEMPORARY: quitting...\n");
}

void	set_sigaction(struct sigaction *sa)
{
	sa->sa_handler = &sig_handler;
	// sa->sa_mask = 0;
	// sa->sa_flags = 0;
	// sa->sa_mask = sigemptyset(0);
	sigaction(SIGINT, sa, 0);
	sigaction(SIGQUIT, sa, 0);
}
