/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:32:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/02 23:30:20 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Specifically designed as a failsafe for env variables overflow
// Also frees the t_list passed in arguments
char	*_exit_var_overflow(t_list **lst)
{
	ft_lstclear(lst, free);
	ft_putendl_fd("minishell: maximum env variable size exceeded", 2);
	kill(0, SIGKILL);
	return (0);
}

int	_exit_err(char *err_msg, char *command, int exit_code, int ret)
{
	ft_putstr_fd(command, 2);
	ft_putendl_fd(err_msg, 2);
	g_exit = exit_code << 8;
	return (ret);
}

int _error(const char *s, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	perror(s);
	return (ret);
}