/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:57:05 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 17:17:53 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*extract_to_lst(char *str)
{
	t_list			*lst;
	unsigned int	i;

	i = 0;
	lst = 0;
	while (str[i])
	{
		while (str[i] && !is_quote(str[i]))
			i++;
		if (i)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(str, i)));
			str += i;
			i = 0;
		}
		if (is_quote(str[i]))
		{
			ft_lstadd_back(&lst, ft_lstnew(
					ft_strndup(str, get_next_quote_pos(str) + 1)));
			str += get_next_quote_pos(str) + 1;
		}
	}
	return (lst);
}

static char	*parsed_lst_to_str(t_list *lst)
{
	size_t	len;
	t_list	*iterator;
	char	*str;

	iterator = lst;
	len = 1;
	while (iterator)
	{
		len += ft_strlen(iterator->content);
		iterator = iterator->next;
	}
	str = ft_calloc(len, 1);
	if (!str)
		return (0);
	while (lst)
	{
		ft_strlcat(str, lst->content, len);
		lst = lst->next;
	}
	return (str);
}

static int	extract_and_expand(t_env *env, char **str)
{
	t_list	*lst;
	t_list	*iterator;

	lst = extract_to_lst(*str);
	iterator = lst;
	while (iterator)
	{
		if (iterator->content[0] != '\'')
			iterator->content = expand(env, iterator->content);
		if (!iterator->content)
			return (-1);
		delete_quotes(iterator->content);
		iterator = iterator->next;
	}
	free(*str);
	*str = parsed_lst_to_str(lst);
	ft_lstclear(&lst, &free);
	return (0);
}

void	parse_quotes(t_command *cmd_lst)
{
	unsigned int	i;
	t_redirect		*iterator;

	while (cmd_lst)
	{
		i = 0;
		while (cmd_lst->args[i])
		{
			extract_and_expand(cmd_lst->env, &cmd_lst->args[i]);
			if (i == 0)
				cmd_lst->args = realloc_if_needed(cmd_lst->args);
			i++;
		}
		if (cmd_lst->redirects)
		{
			iterator = cmd_lst->redirects;
			while (iterator)
			{
				extract_and_expand(cmd_lst->env, &iterator->redir_name);
				iterator = iterator->next;
			}
		}
		cmd_lst->command = cmd_lst->args[0];
		cmd_lst = cmd_lst->next;
	}
}
