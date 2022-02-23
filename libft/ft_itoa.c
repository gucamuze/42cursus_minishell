/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:49:13 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:30 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	get_malloc_size(int n)
{
	unsigned int	nb;
	size_t			len;

	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	len = 2;
	while (nb >= 10)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	size_t			str_len;

	str_len = get_malloc_size(n);
	if (n < 0)
		str_len++;
	str = malloc(str_len * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	*(str + --str_len) = '\0';
	while (nb >= 10)
	{
		*(str + --str_len) = (nb % 10) + 48;
		nb /= 10;
	}
	*(str + --str_len) = (nb % 10) + 48;
	if (n < 0)
		*(str + --str_len) = '-';
	return (str);
}
