/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 03:51:39 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/17 03:51:49 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

unsigned int	get_next_quote_pos(char *str)
{
	unsigned int	j;
	char			quote;

	j = 1;
	quote = str[0];
	while (str[j] && str[j] != quote)
		j++;
	return (j);
}

int	check_unending_quotes(char *command)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (command[i])
	{
		if (is_quote(command[i]))
		{
			j = get_next_quote_pos(&command[i]);
			if (!command[i + j])
				return (0);
			else
				i += j;
		}
		i++;
	}
	return (1);
}
