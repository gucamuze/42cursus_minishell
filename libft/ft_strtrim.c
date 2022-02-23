/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 01:02:38 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:30 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	is_in_set(char const *set, char c)
{
	unsigned int	index;

	index = 0;
	while (*(set + index))
	{
		if (*(set + index) == c)
			return (1);
		index++;
	}
	return (0);
}

static char	*ft_return_empty_str(void)
{
	char	*trimed_str;

	trimed_str = malloc(1);
	if (!trimed_str)
		return (NULL);
	trimed_str[0] = '\0';
	return (trimed_str);
}

size_t	set_str_size(unsigned int start_i, unsigned int end_i, size_t str_len)
{
	if (start_i == (unsigned int)str_len)
		return (1);
	return (end_i - start_i + 2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start_index;
	unsigned int	end_index;
	unsigned int	strtrim_index;
	size_t			str_size;
	char			*trimed_str;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_return_empty_str());
	start_index = 0;
	while (is_in_set(set, *(s1 + start_index)) && *(s1 + start_index))
		start_index++;
	end_index = ft_strlen(s1);
	while (end_index && is_in_set(set, *(s1 + --end_index)))
		;
	str_size = set_str_size(start_index, end_index, ft_strlen(s1));
	trimed_str = malloc(str_size * sizeof(char));
	if (!trimed_str)
		return (NULL);
	strtrim_index = 0;
	while (start_index <= end_index)
		*(trimed_str + strtrim_index++) = *(s1 + start_index++);
	*(trimed_str + strtrim_index) = '\0';
	return (trimed_str);
}
