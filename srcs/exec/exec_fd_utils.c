/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:05:05 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/30 13:05:32 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_output_redir(t_command *cmd)
{
	int			fd;
	t_redirect	*iterator;
	
	fd = -1;
	iterator = cmd->redirects;
	while (iterator)
	{
		if (iterator->redir_type == 0 || iterator->redir_type == 1)
		{
			if (fd != -1)
				close(fd);
			if (iterator->redir_type == 0)
				fd = open(iterator->redir_name, 01101, 0644);
			else
				fd = open(iterator->redir_name, 02101, 0644);
		}
		iterator = iterator->next;
	}
	if (fd > -1)
		cmd->fds[1] = fd;
	else
		cmd->fds[1] = cmd->pipefds[1];
	// dup2(cmd->fds[1], STDOUT_FILENO);
	return (fd);
}

int	setup_input_redir(t_command *cmd)
{
	int			fd;
	t_redirect	*iterator;
	
	fd = -1;
	iterator = cmd->redirects;
	while (iterator)
	{
		if (iterator->redir_type == 2)
		{
			if (fd != -1)
				close(fd);
			fd = open(iterator->redir_name, O_RDONLY, 0644);
		}
		iterator = iterator->next;
	}
	if (fd > -1)
		cmd->fds[0] = fd;
	else
		cmd->fds[0] = cmd->pipefds[0];
	return (fd);
}

unsigned int	close_all_fds(t_command *cmd)
{
	int	fd0;
	int	fd1;

	fd0 = cmd->pipefds[0];
	fd1 = cmd->pipefds[1];
	while (cmd)
	{
		if (cmd->fds[0] != cmd->pipefds[0])
			close(cmd->fds[0]);
		if (cmd->fds[1] != cmd->pipefds[1])
			close(cmd->fds[1]);
		cmd = cmd->next;
	}
	close(fd0);
	close(fd1);
	return (0);
}