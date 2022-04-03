/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 01:05:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/03 02:17:02 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_persistent_history(char *str, t_env *env)
{
	pid_t	fd;
	char	*history_path;
	char	*homedir;
	
	homedir = get_env_val(env, "HOME", 0);
	if (homedir)
	{
		history_path = ft_strjoin(homedir, "/.ms_history");
		fd = open(history_path, 02101, 0644);
		if (fd == -1)
			return (-1);
		ft_putendl_fd(str, fd);
		return (0);
	}
	return (-1);
}

char	**create_history(int fd)
{
	char			buffer[2048];
	char			**split;
	char			*str;
	t_list			*lst;
	unsigned int	i;

	lst = 0;
	memset(&buffer[0], 0, 2048);
	while (read(fd, &buffer[0], 2048) > 0)
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(buffer)));
	str = lst_to_str(lst);
	split = ft_split(str, '\n');
	free(str);
	i = 0;
	while (split[i])
		add_history(split[i++]);
	return (split);
}

int	import_history(char **history, t_env *env)
{
	pid_t	fd;
	char	*history_path;
	char	*homedir;
	
	(void)history;
	homedir = get_env_val(env, "HOME", 0);
	if (homedir)
	{
		history_path = ft_strjoin(homedir, "/.ms_history");
		fd = open(history_path, O_RDONLY, 0644);
		if (fd == -1)
			return (_error(history_path, -1));
		history = create_history(fd);
		return (0);
	}
	return (-1);
}

