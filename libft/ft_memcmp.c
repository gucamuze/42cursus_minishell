/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 02:11:10 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:30 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;
	size_t				index;

	ptr_s1 = s1;
	ptr_s2 = s2;
	index = 0;
	while (index < n)
	{
		if (*(ptr_s1 + index) != *(ptr_s2 + index))
			return (*(ptr_s1 + index) - *(ptr_s2 + index));
		index++;
	}
	return (0);
}
