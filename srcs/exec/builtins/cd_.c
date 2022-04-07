/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:50:34 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/07 20:58:19 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd_(t_command *cmd, int exit, char *oldpwd)
{
	free(oldpwd);
	if (exit)
		return (_exit_err(" HOME not set", cmd, 1, 1));
	return (_error(cmd->args[1], 1));
}
