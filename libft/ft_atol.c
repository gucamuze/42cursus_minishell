/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:46:07 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 17:52:21 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long long int	ft_atol(const char *nptr)
{
	int					sign;
	long long int		result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr++ - 48);
	}
	return (sign * result);
}
