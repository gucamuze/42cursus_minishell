/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:09:38 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:30 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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

static char	*create_str(const char *s, size_t size)
{
	char			*new_str;
	unsigned int	index;

	new_str = malloc((size + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	index = 0;
	while (index < size)
	{
		*(new_str + index) = *(s + index);
		index++;
	}
	*(new_str + index) = '\0';
	return (new_str);
}

char	**ft_split(const char *s, char c)
{
	char			**tab;
	unsigned int	tab_index;
	unsigned int	str_i;
	unsigned int	str_l;

	if (!s)
		return (NULL);
	tab = malloc(get_word_count(s, c) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab_index = 0;
	str_i = 0;
	while (*(s + str_i))
	{
		str_l = 0;
		while (is_separator(*(s + str_i), c))
			str_i++;
		while (!(is_separator(*(s + str_i + str_l), c)) && *(s + str_i + str_l))
			str_l++;
		if (str_l > 0)
			*(tab + tab_index++) = create_str(&*(s + str_i), str_l);
		str_i += str_l;
	}
	*(tab + tab_index) = NULL;
	return (tab);
}
