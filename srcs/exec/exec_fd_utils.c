/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:05:05 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/28 21:23:36 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_output_redir(t_command *cmd)
{
	int	fd;
	
	fd = -1;
	while (cmd->redirects)
	{
		if (cmd->redirects->redir_type == 0 || cmd->redirects->redir_type == 1)
		{
			if (fd != -1)
				close(fd);
			if (cmd->redirects->redir_type == 0)
				fd = open(cmd->redirects->redir_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(cmd->redirects->redir_name, 02101, 0644);
		}
		cmd->redirects = cmd->redirects->next;
	}
	if (fd > -1)
	{
		close(cmd->fds[1]);
		cmd->fds[1] = fd;
		dup2(cmd->fds[1], STDOUT_FILENO);
	}
	return (fd);
}

int	setup_input_redir(t_command *cmd)
{
	int	fd;
	
	fd = -1;
	while (cmd->redirects)
	{
		if (cmd->redirects->redir_type == 2)
		{
			if (fd != -1)
				close(fd);
			fd = open(cmd->redirects->redir_name, O_RDONLY, 0644);
		}
		cmd->redirects = cmd->redirects->next;
	}
	if (fd > -1)
	{
		close(cmd->fds[0]);
		cmd->fds[0] = fd;
		dup2(cmd->fds[0], STDIN_FILENO);
	}
	return (fd);
}

unsigned int	close_all_fds(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->fds[0] != -1)
			close(cmd->fds[0]);
		if (cmd->fds[1] != -1)
			close(cmd->fds[1]);
		cmd = cmd->next;
	}
	return (0);
}