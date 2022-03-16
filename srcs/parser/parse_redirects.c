/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:12:56 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/16 05:33:11 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	create_output_redirect(t_command *cmd, char *str)
{
	unsigned int	j;
	unsigned int	type;
	char			*name;
	
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
	return (1);
}

static unsigned int	create_input_redirect(t_command *cmd, char *str)
{
	unsigned int	j;
	unsigned int	type;
	char			*name;
	
	j = 1;
	type = 2;
	if (str[j] == '<')
	{
		type = 3;
		j++;
	}
	name = get_redirect_name(&str[j]);
	if (!name)
		return (0);
	redir_lst_add_back(&cmd->redirects, redir_lst_new(type, name));
	update_command(str);
	return (1);
}

static unsigned int create_redirects(t_command *cmd, char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			str += get_next_quote_pos(str) + 1;
		else if (*str == '>')
		{
			if (!create_output_redirect(cmd, str))
				return (0);
		}		
		else if (*str == '<')
		{
			if (!create_input_redirect(cmd, str))
				return (0);
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
		if (!create_redirects(cmd_lst, cmd_lst->command))
			return (0);
		cmd_lst = cmd_lst->next;
	}
	return (1);
}