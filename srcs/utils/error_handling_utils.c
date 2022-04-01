/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:32:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/01 16:10:35 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exit_err(char *err_msg, char *command, int exit_code, int ret)
{
	ft_putstr_fd(err_msg, 2);
	ft_putendl_fd(command, 2);
	g_exit = exit_code << 8;
	return (ret);
}

int _error(const char *s, int ret)
{
	perror(s);
	return (ret);
}