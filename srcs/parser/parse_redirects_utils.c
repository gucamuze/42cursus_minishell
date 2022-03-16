/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 05:33:20 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/16 05:51:46 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	is_valid_redir_char(char c)
{
	if (c == ' ' || c == '<' || c == '>')
		return (0);
	return (1);
}

// The char *str parameter should be right after the last redirect character
char	*get_redirect_name(char *str)
{
	unsigned int	j;

	while (*str == ' ')
		str++;
	if (*str == '>' || *str == '<')
		return (0);
	while (*str)
	{
		j = 0;
		if (*str == '\'' || *str == '\"')
			j += get_next_quote_pos(str) + 1;
		else
			while (str[j] && is_valid_redir_char(str[j]))
				j++;
		if (j)
			return (ft_strndup(str, j));
		str++;
	}
	return (0);
}

// The char *str parameter should be on the first redirect character
void	update_command(char *str)
{
	unsigned int	j;

	j = 0;
	while (str[j] && !is_valid_redir_char(str[j]))
		j++;
	if (is_quote(str[j]))
		j += get_next_quote_pos(&str[j]) + 1;
	else
		while (str[j] && is_valid_redir_char(str[j]))
			j++;
	if (!str[j])
		str[0] = 0;
	else
		ft_memmove(str, &str[j], ft_strlen(&str[j]) + 1); // memory magic, +1 to include the null char
}