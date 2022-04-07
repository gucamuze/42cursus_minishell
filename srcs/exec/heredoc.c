/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:00:27 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/07 20:21:25 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_heredocs(t_command *cmd_lst)
{
	t_redirect	*iterator;

	while (cmd_lst)
	{
		iterator = cmd_lst->redirects;
		while (iterator)
		{
			if (iterator->redir_type == 3)
				cmd_lst->fd_in = heredoc(cmd_lst, iterator);
			iterator = iterator->next;
		}
		cmd_lst = cmd_lst->next;
	}
	return (0);
}

static int	forked_heredoc(t_command *cmd, t_redirect *redirect, int fd)
{
	char	*s;

	(void)cmd;
	set_signals(1);
	if (fd == -1)
		exit(_error(redirect->redir_name, -1));
	s = readline("heredoc> ");
	while (s != NULL && ft_strcmp(s, redirect->redir_name))
	{
		ft_putendl_fd(s, fd);
		free(s);
		s = readline("heredoc> ");
	}
	if (s == NULL)
		write(1, "\n", 1);
	close(fd);
	exit(0);
}

static int	parent_heredoc(t_redirect *redir, char *file, pid_t pid, int fd)
{
	int		fork_ret;

	set_signals(2);
	waitpid(pid, &fork_ret, 0);
	set_signals(0);
	if (g_exit >> 8 == 130 || g_exit >> 8 == 131)
	{
		free(file);
		return (-2);
	}
	if (fork_ret >> 8 == -1)
		return (-1);
	free(redir->redir_name);
	redir->redir_name = file;
	close(fd);
	return (fd);
}

int	heredoc(t_command *cmd, t_redirect *redirect)
{
	char	*file_name;
	int		fd;
	pid_t	pid;

	file_name = setup_filename(redirect->redir_name);
	fd = open(file_name, 01101, 0664);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		forked_heredoc(cmd, redirect, fd);
	else
		return (parent_heredoc(redirect, file_name, pid, fd));
	return (-1);
}
