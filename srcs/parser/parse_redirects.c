/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:12:56 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/16 04:45:05 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	is_valid_redir_char(char c)
{
	if (c == ' ' || c == '<' || c == '>')
		return (0);
	return (1);
}

// The char *str parameter should be right after the last redirect character
static char	*get_redirect_name(char *str)
{
	unsigned int	j;

	while (*str == ' ')
		str++;
	if (*str == '>' || *str == '<')
		return (0);
	while (*str)
	{
		j = 0;
		while (str[j] && is_valid_redir_char(str[j]))
			j++;
		if (j)
			return (ft_strndup(str, j + 1));
		str++;
	}
	return (0);
}

// The char *str parameter should be on the first redirect character
static void	update_command(char *str)
{
	unsigned int	j;

	j = 0;
	while (str[j] && !is_valid_redir_char(str[j]))
		j++;
	while (str[j] && is_valid_redir_char(str[j]))
		j++;
	if (!str[j])
		str[0] = 0;
	else
		ft_memmove(str, &str[j], ft_strlen(&str[j]) + 1); // magie noire eh
}

static unsigned int create_output_redirects(t_command *cmd, char *str)
{
	unsigned int	j;
	unsigned int	type;
	char			*name;

	while (*str)
	{
		if (*str == '>')
		{
			j = 1;
			type = 0;
			if (str[j] == '>')
			{
				type = 1;
				j++;
			}
			name = get_redirect_name(&str[j]);
			if (!name)
				return (0);
			redir_lst_add_back(&cmd->redirects, redir_lst_new(type, name));
			update_command(str);
		}
		else
			str++;
	}
	return (1);
}

int	parse_redirects(t_command *cmd_lst)
{
	while (cmd_lst)
	{
		if (!create_output_redirects(cmd_lst, cmd_lst->command))
			return (0);
		cmd_lst = cmd_lst->next;
	}
	return (1);
}