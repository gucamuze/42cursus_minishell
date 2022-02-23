/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 03:46:20 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:30 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while ((*(s1 + index) || *(s2 + index)) && index < n)
	{
		if (*(s1 + index) != *(s2 + index))
		{
			if ((unsigned char)*(s1 + index) > (unsigned char)*(s2 + index))
				return (1);
			else
				return (-1);
		}
		index++;
	}
	return (0);
}
