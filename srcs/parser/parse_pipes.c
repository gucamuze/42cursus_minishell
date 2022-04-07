/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:08:07 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/07 20:23:43 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_invalid_pipes(t_list *parsed_pipes)
{
	while (parsed_pipes)
	{
		if (str_is_empty(parsed_pipes->content))
			return (0);
		parsed_pipes = parsed_pipes->next;
	}
	return (1);
}

t_list	*parse_pipes_loop(char *user_input, t_list *lst, int i, int j)
{
	while (user_input[i])
	{
		if (user_input[i] == '|')
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(user_input, i)));
			user_input += i + 1;
			i = 0;
		}
		else if (user_input[i] == '\'' || user_input[i] == '\"')
		{
			j = 1;
			while (user_input[i + j] && user_input[i + j] != user_input[i])
				j++;
			i += j;
		}
		else
			i++;
		if (!user_input[i])
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(user_input, i)));
	}
	return (lst);
}

// Frees the user_input
// !!! DOES NOT CHECK FOR INVALID QUOTES AND WILL FUCK UP IF THERE IS ANY !!!!!
t_list	*parse_pipes(char *user_input)
{
	unsigned int	i;
	unsigned int	j;
	t_list			*lst;

	i = 0;
	j = 0;
	lst = NULL;
	return (parse_pipes_loop(user_input, lst, i, j));
}
