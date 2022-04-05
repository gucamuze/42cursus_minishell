/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:05:05 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/05 18:36:11 by malbrand         ###   ########.fr       */
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
			if (fd == -1)
				return (_error(iterator->redir_name, 0));
		}
		iterator = iterator->next;
	}
	if (fd > -1)
	{
		close(cmd->fds[1]);
		cmd->fds[1] = fd;
	}
	else if (!cmd->next)
	{
		close(cmd->fds[1]);
		cmd->fds[1] = dup(STDOUT_FILENO);
	}
	return (1);
}

static int	setup_fd_input(t_redirect *red)
{
	int	fd;

	fd = 0;
	if (red->redir_type == 2)
		fd = open(red->redir_name, O_RDONLY, 0644);
	else
		fd = herdoc(red);
	return (fd);
}

int	setup_input_redir(t_command *cmd)
{
	int			fd;
	t_redirect	*iterator;
	
	fd = -1;
	iterator = cmd->redirects;
	if (cmd->next)
		cmd->next->fd_in = cmd->fds[0];
	while (iterator)
	{
		if (iterator->redir_type == 2 || iterator->redir_type == 3)
		{
			if (fd != -1)
				close(fd);
			fd = setup_fd_input(iterator);
			if (fd == -1)
				return (_error(iterator->redir_name, 0));
		}
		iterator = iterator->next;
	}
	if (fd > -1)
		cmd->fd_in = fd;
	return (1);
}

unsigned int	close_all_fds(t_command *cmd)
{
	t_redirect	*iterator;

	iterator = cmd->redirects;
	while (cmd)
	{
		if (cmd->fds[0] > 2)
			close(cmd->fds[0]);
		if (cmd->fds[1] > 2)
			close(cmd->fds[1]);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		cmd = cmd->next;
	}
	while (iterator)
	{
		if (iterator->redir_type == 3)
		{
			unlink(iterator->tmp_herdoc);
			free(iterator->tmp_herdoc);
		}
		iterator = iterator->next;
	}
	return (0);
}
