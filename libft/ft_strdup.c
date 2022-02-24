/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:49:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/24 18:08:22 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char			*dup;
	size_t			len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (0);
	while (*s)
		*dup++ = *s++;
	*dup = 0;
	return (dup - len);
}
