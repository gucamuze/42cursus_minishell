/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:19:09 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/03 21:05:12 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*ptr;
	long long int	check_overflow;
	unsigned int	index;

	check_overflow = size * nmemb;
	if (check_overflow > 2147483647)
		return (NULL);
	ptr = malloc(check_overflow);
	if (!ptr)
		return (NULL);
	index = 0;
	while (index < check_overflow)
		*(ptr + index++) = 0;
	return ((void *)ptr);
}
