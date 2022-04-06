/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 05:14:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 17:27:54 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Frees the list given as parameter
char	*lst_to_str(t_list *lst)
{
	t_list	*iterator;
	size_t	strsize;
	char	*str;

	iterator = lst;
	strsize = 0;
	while (iterator)
	{
		strsize += ft_strlen(iterator->content);
		iterator = iterator->next;
	}
	str = ft_calloc(1, strsize + 1);
	if (!str)
		return (0);
	iterator = lst;
	while (iterator)
	{
		ft_strlcat(str, iterator->content, strsize + 1);
		iterator = iterator->next;
	}
	ft_lstclear(&lst, free);
	return (str);
}

// Returns the length of the env variable it expanded
static unsigned int	expand_env_var(t_env *env, char *str, char **expanded)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str[i++] == '$')
	{
		if (str[i++] == '?')
			*expanded = ft_itoa(g_exit >> 8);
		else
		{
			i = 0;
			while (str[++i] && ft_isalpha(str[i]))
				;
			tmp = ft_strncpy(&str[1], i - 1);
			*expanded = get_env_val(env, tmp, 1);
			free(tmp);
		}
	}
	else if (str[0] == '~')
	{
		*expanded = get_env_val(env, "HOME", 1);
		i = 1;
	}
	return (i);
}

char	*expand(t_env *env, char *str)
{
	int				i;
	char			*tmp;
	t_list			*lst;

	i = 0;
	lst = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1]) || str[i] == '~')
		{
			if (i)
				ft_lstadd_back(&lst, ft_lstnew(ft_strndup(str, i)));
			str += expand_env_var(env, str + i, &tmp) + i;
			if (tmp)
				ft_lstadd_back(&lst, ft_lstnew(tmp));
			i = 0;
		}
		else
			i++;
	}
	if (i)
		ft_lstadd_back(&lst, ft_lstnew(ft_strndup(str, i)));
	return (lst_to_str(lst));
}
