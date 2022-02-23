/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:48:47 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:30 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_i;
	size_t	src_i;

	dst_i = 0;
	while (dst[dst_i] && dst_i < size)
		dst_i++;
	src_i = 0;
	while (src[src_i] && (src_i + dst_i + 1) < size)
	{
		dst[dst_i + src_i] = src[src_i];
		src_i++;
	}
	if (dst_i < size)
		dst[dst_i + src_i] = '\0';
	return (ft_strlen(src) + dst_i);
}
