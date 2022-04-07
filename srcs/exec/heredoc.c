/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:00:27 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/06 22:42:15 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*change_name(char *s, int point)
{
	int		i;
	int		j;
	int		len;
	char	*file_name;

	i = 0;
	j = 0;
	len = ft_strlen(s) + point + 1;
	file_name = (char *)malloc(sizeof(char) * len + 1);
	if (file_name == NULL)
		return (NULL);
	while (i < point)
		file_name[i++] = '.';
	while (i < len)
		file_name[i++] = s[j++];
	file_name[i] = 0;
	return (file_name);
}

static char	*setup_filename(char *s)
{
	int		point;
	char	*file_name;

	point = 0;
	file_name = ft_strdup(s);
	while (access(file_name, F_OK) != -1)
	{
		point++;
		free(file_name);
		file_name = change_name(s, point);
	}
	return (file_name);
}

static int	forked_heredoc(t_redirect *redirect)
{
	char	*s;
	char	*file_name;
	int		fd;

	set_signals(1);
	file_name = setup_filename(redirect->redir_name);
	fd = open(file_name, 01101, 0664);
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
	free(redirect->redir_name);
	redirect->redir_name = file_name;
	exit(0);
}

int	heredoc(t_redirect *redirect)
{
	pid_t	pid;
	int		fork_ret;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		forked_heredoc(redirect);
	else
	{
		set_signals(2);
		waitpid(pid, &fork_ret, 0);
		set_signals(0);
		if (fork_ret >> 8 == 130 || fork_ret >> 8 == 131)
			return (-2);
		if (fork_ret >> 8 == -1)
			return (-1);
	}
	return (0);
}
