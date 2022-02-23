/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:49:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/23 15:24:23 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char			*dup;

	if (!s)
		return (0);
	dup = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (*s)
		*dup++ = *s++;
	*dup = 0;
	return (dup);
}
