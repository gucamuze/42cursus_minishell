/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:49:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/02 23:35:32 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char			*dup;
	size_t			len;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (0);
	while (*s)
		*dup++ = *s++;
	*dup = 0;
	return (dup - len);
}
