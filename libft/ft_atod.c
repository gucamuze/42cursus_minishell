/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:24:19 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/05 16:24:45 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	get_index_after_decimal(char *str)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (str[index] == '.')
		{
			index++;
			break ;
		}
	}
	return (index);
}

double	ft_atod(char *str)
{
	double	first_part;
	double	second_part;
	double	negative;
	int		index_post_decimal;

	negative = 1;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	first_part = (double)ft_atoi(str);
	index_post_decimal = get_index_after_decimal(str);
	str += index_post_decimal;
	if (*str && ft_isdigit(*str))
		second_part = (double)ft_atoi(str);
	else
		second_part = 0;
	index_post_decimal = ft_strlen(str);
	while (index_post_decimal--)
		second_part /= 10;
	return ((first_part + second_part) * negative);
}
