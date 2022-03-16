/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:57:05 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/16 02:37:52 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (command[i] == '\'' || command[i] == '\"')
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
