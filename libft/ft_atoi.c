/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:46:07 by gucamuze          #+#    #+#             */
/*   Updated: 2021/09/08 15:53:55 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	int					sign;
	long long int		result;
	char				decimals;

	sign = 1;
	result = 0;
	decimals = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr++ - 48);
		decimals++;
		if (decimals > 18)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
	}
	return (sign * result);
}
