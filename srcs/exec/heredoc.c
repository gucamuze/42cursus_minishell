/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:00:27 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/08 03:32:52 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_heredocs(t_data *data, t_command *cmd_lst)
{
	t_redirect	*iterator;

	while (cmd_lst)
	{
		iterator = cmd_lst->redirects;
		while (iterator)
		{
			if (iterator->redir_type == 3)
			{
				if (cmd_lst->fd_in != -1)
					close(cmd_lst->fd_in);
				if (heredoc(data, iterator) < 0)
					return (_error("heredoc error", -1));
			}
			iterator = iterator->next;
		}
		cmd_lst = cmd_lst->next;
	}
	return (0);
}

static int	forked_heredoc(
	t_data *data, char *filename, t_redirect *redirect, int fd)
{
	char	*s;
	char	redir_name[16384];

	ft_memset(redir_name, 0, 16384);
	ft_memcpy(redir_name, redirect->redir_name,
		ft_strlen(redirect->redir_name));
	free(filename);
	cmd_lst_free(data->first_cmd);
	cleanup(data);
	set_signals(3);
	s = readline("heredoc> ");
	while (s != NULL && ft_strcmp(s, redir_name))
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

	set_signals(4);
	waitpid(pid, &fork_ret, 0);
	printf("fork ret => %d\n", fork_ret);
	close(fd);
	set_signals(0);
	if (fork_ret == 130 << 8 || fork_ret == 131 << 8)
	{
		free(file);
		return (-2);
	}
	if (fork_ret >> 8 == -1)
		return (-1);
	free(redir->redir_name);
	redir->redir_name = file;
	return (0);
}

int	heredoc(t_data *data, t_redirect *redirect)
{
	char	*file_name;
	int		fd;
	pid_t	pid;

	file_name = setup_filename(redirect->redir_name);
	fd = open(file_name, 01101, 0664);
	if (fd == -1)
		return (_error("open", -1));
	pid = fork();
	if (pid == -1)
	{
		free(file_name);
		close(fd);
		return (_error("fork", -1));
	}
	if (pid == 0)
		forked_heredoc(data, file_name, redirect, fd);
	else
		return (parent_heredoc(redirect, file_name, pid, fd));
	return (-1);
}
