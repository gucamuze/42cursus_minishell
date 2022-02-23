/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 00:17:09 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:30 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	size;
	unsigned int	s1_index;
	unsigned int	s2_index;
	char			*strjoin;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	strjoin = malloc(size * sizeof(char));
	if (!strjoin)
		return (NULL);
	s1_index = 0;
	while (*(s1 + s1_index))
	{
		*(strjoin + s1_index) = *(s1 + s1_index);
		s1_index++;
	}
	s2_index = 0;
	while (*(s2 + s2_index))
	{
		*(strjoin + s1_index + s2_index) = *(s2 + s2_index);
		s2_index++;
	}
	*(strjoin + s1_index + s2_index) = '\0';
	return (strjoin);
}
