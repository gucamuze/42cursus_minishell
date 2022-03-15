/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:57:05 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/15 22:17:33 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_single_quotes(char *str)
{
	
}

static char *parse_double_quotes(char *str)
{
	
}

char	*parse_quotes(t_env *env, char *user_input)
{
	unsigned int	i;
	t_list			*lst;
	char			*str;

	i = 0;
	lst = 0;
	while (*user_input)
	{
		if (user_input[i] == '\'' || user_input[i] == '\"')
		{
			str = malloc(i + 2);
			if (!str)
				return (0);
			ft_lstadd_back(&lst, ft_lstnew());
		}
		user_input++;
		i++;
	}
}