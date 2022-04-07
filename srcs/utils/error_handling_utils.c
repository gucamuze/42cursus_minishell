/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:32:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/07 20:41:42 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Specifically designed as a failsafe for env variables overflow
// Also frees the t_list passed in arguments
char	*_exit_var_overflow(t_list **lst)
{
	ft_lstclear(lst, free);
	ft_putendl_fd("minishell: maximum variable size exceeded", 2);
	return (0);
}

int	_exit_err(char *err_msg, t_command *cmd, int exit_code, int ret)
{
	ft_putstr_fd(cmd->command, 2);
	ft_putendl_fd(err_msg, 2);
	cmd->exit_code = exit_code;
	return (ret);
}

int	_error(const char *s, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	perror(s);
	return (ret);
}

// 0 for quotes, 1 for pipes, 2 for redirects
int	dispatcher_error(t_list *pipes, t_command *cmd_lst, int mode)
{
	if (mode == 1)
		if (pipes)
			ft_lstclear(&pipes, free);
	if (mode == 2)
		if (cmd_lst)
			cmd_lst_free_if_error(cmd_lst);
	if (mode == 0)
		ft_putstr_fd(INVALID_QUOTES, 2);
	if (mode == 1)
		ft_putstr_fd(INVALID_PIPES, 2);
	if (mode == 2)
		ft_putstr_fd(INVALID_REDIRECT, 2);
	return (0);
}
