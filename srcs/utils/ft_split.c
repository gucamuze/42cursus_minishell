/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:16:58 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/03 02:47:20 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	is_separator(char c, char separator)
{
	if (c == separator)
		return (1);
	return (0);
}

static unsigned int	get_word_count(const char *s, char c)
{
	unsigned int	index;
	unsigned int	count;

	index = 0;
	count = 1;
	while (*(s + index))
	{
		while (is_separator(*(s + index), c) && *(s + index))
			index++;
		if (!(is_separator(*(s + index), c)) && *(s + index))
		{
			count++;
			while (!(is_separator(*(s + index), c)) && *(s + index))
				index++;
		}
	}
	return (count);
}

static char	*ft_strndup(const char *s, unsigned int n)
{
	char			*dup;

	if (!s)
		return (0);
	dup = malloc((n + 1) * sizeof(char));
	if (!dup)
		return (0);
	ft_memcpy(dup, s, n);
	*(dup + n) = 0;
	return (dup);
}

void	free_split(char **split)
{
	unsigned int	i;

	i = 0;
	if (split)
	{
		while (split[i])
			free(split[i++]);
		free(split);
	}
}

char	**ft_split2(const char *s, char c)
{
	char			**tab;
	unsigned int	str_l;
	unsigned int	i;

	if (!s)
		return (NULL);
	tab = malloc(get_word_count(s, c) + 1 * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		str_l = 0;
		while (is_separator(*s, c))
			s++;
		while (*(s + str_l) && !is_separator(*(s + str_l), c))
			str_l++;
		tab[i++] = ft_strndup(s, str_l);
		s += str_l;
	}
	tab[i] = 0;
	return (tab);
}
