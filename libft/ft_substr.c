/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 23:18:43 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:30 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	index;

	index = 0;
	if (start < ft_strlen(s))
	{
		while (*(s + start + index) && index < len)
			index++;
		substr = malloc((index + 1) * sizeof(char));
		if (!substr)
			return (NULL);
		index = 0;
		while (*(s + start + index) && index < len)
		{
			*(substr + index) = *(s + start + index);
			index++;
		}
	}
	else
		substr = malloc(1);
	if (!substr)
		return (NULL);
	*(substr + index) = '\0';
	return (substr);
}
