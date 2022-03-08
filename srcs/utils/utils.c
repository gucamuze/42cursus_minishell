/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:37:46 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/08 19:05:26 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;
	size_t	len3;
	size_t	total_len;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	total_len = len1 + len2 + len3;
	new_str = malloc(total_len + 1);
	if (!new_str)
		return (0);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2);
	ft_memcpy(new_str + len1 + len2, s3, len3);
	new_str[total_len] = 0;
	return (new_str);
}

char	*ft_strncpy(char *str, size_t size)
{
	char	*cpy;
	int		i;

	cpy = malloc(size + 1);
	if (!cpy)
		return (0);
	i = -1;
	while (str[++i] && size--)
		cpy[i] = str[i];
	cpy[i] = 0;
	// printf("cpy done => %s\n", cpy);
	return (cpy);
}
