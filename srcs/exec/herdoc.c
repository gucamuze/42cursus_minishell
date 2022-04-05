/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:00:27 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/05 19:17:39 by malbrand         ###   ########.fr       */
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
	{
		file_name[i] = '.';
		i++;
	}
	while (i < len)
	{
		file_name[i] = s[j];
		i++;
		j++;
	}
	file_name[i] = '\0';
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

static int	free_herdoc(char *s, int fd, char *file_name)
{
	if (!s)
	{
		close(fd);
		unlink(file_name);
		free(file_name);
		return (-1);
	}
	return (0);
}

int	herdoc(t_redirect *iterator)
{
	int		fd;
	int		len;
	char	*s;
	char	*file_name;

	file_name = setup_filename(iterator->redir_name);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	s = readline(">");
	if (free_herdoc(s, fd, file_name) == -1)
		return (-1);
	len = ft_strlen(s);
	while (s != NULL && ft_strncmp(s, iterator->redir_name, len) != 0)
	{
		write(fd, s, len);
		write(fd, "\n", 1);
		free(s);
		s = readline(">");
		if (free_herdoc(s, fd, file_name) == -1)
			return (-1);
		len = ft_strlen(s);
	}
	close (fd);
	fd = open(file_name, O_RDONLY, 0644);
	iterator->tmp_herdoc = file_name;
	return (fd);
}
