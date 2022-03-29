/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:05:05 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/29 16:33:51 by gucamuze         ###   ########.fr       */
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
	{
		close(cmd->fds[1]);
		printf("file fd => %d\n", fd);
		cmd->fds[1] = fd;
		dup2(cmd->fds[1], STDOUT_FILENO);
	}
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