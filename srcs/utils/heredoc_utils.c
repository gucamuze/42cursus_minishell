/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:54:39 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/07 19:55:15 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_name(char *s, int point)
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

char	*setup_filename(char *s)
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
