/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:49:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/24 17:48:05 by gucamuze         ###   ########.fr       */
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
	{
		*dup = *s;
		printf("%c and %c\n", *dup, *s);
		dup++;
		s++;
	}
	*dup = 0;
	return (dup - len);
}

// char	*ft_strdup(const char *s)
// {
// 	char			*dup;
// 	unsigned int	i;

// 	if (!s)
// 		return (0);
// 	dup = malloc(ft_strlen(s));
// 	if (!dup)
// 		return (0);
// 	i = 0;
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = 0;
// 	return (dup);
// }