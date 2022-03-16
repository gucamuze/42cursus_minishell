/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:12:56 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/16 04:15:12 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	is_valid_redir_char(char c)
{
	if (c == ' ' || c == '<' || c == '>')
		return (0);
	return (1);
}

static char	*get_redirect_name(char *str)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && is_valid_redir_char(str[i + j]))
			j++;
		if (j)
			return (ft_strndup(&str[i], j + 1));
		i++;
	}
	return (0);
}

void	update_command(char *str)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && is_valid_redir_char(str[i + j]))
			j++;
		if (j)
		{
			if (!str[i + j])
				str[0] = 0;
			else
				ft_memmove(str, &str[i + j], ft_strlen(&str[i + j]) + 1); // magie noire eh
			break ; 
		}
		i++;
	}
}

static unsigned int create_output_redirects(t_command *cmd, char *str)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	redir_type;
	char			*redir_name;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			printf("str in main func => %s\n", str);
			j = 1;
			redir_type = 0;
			if (str[i + j] == '>')
			{
				redir_type = 1;
				j++;
			}
			redir_name = get_redirect_name(&str[i + j]);
			redir_lst_add_back(&cmd->redirects,
				redir_lst_new(redir_type, redir_name));
			update_command(&cmd->command[i]);
			i = 0;
		}
		else
			i++;
	}
	return 0;
}

int	parse_redirects(t_command *cmd_lst)
{
	while (cmd_lst)
	{
		create_output_redirects(cmd_lst, cmd_lst->command);
		cmd_lst = cmd_lst->next;
	}
	return (1);
}