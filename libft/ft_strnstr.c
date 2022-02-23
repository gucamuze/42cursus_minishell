/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 04:47:22 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:30 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h_index;
	size_t	n_index;

	if (*needle == '\0')
		return ((char *)haystack);
	h_index = 0;
	while (*(haystack + h_index) && h_index < len)
	{
		n_index = 0;
		if (*(haystack + h_index) == *(needle + n_index))
		{
			while (*(needle + n_index) && h_index + n_index < len
				&& *(haystack + h_index + n_index) == *(needle + n_index))
			{
				n_index++;
			}
			if (*(needle + n_index) == '\0')
				return ((char *)haystack + h_index);
		}
		h_index++;
	}
	return (NULL);
}
