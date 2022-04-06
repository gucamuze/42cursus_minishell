/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 23:37:17 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 21:46:32 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_lst_free(t_redirect *redir_lst)
{
	if (redir_lst)
	{
		if (redir_lst->redir_name)
			free(redir_lst->redir_name);
		if (redir_lst->next)
			redir_lst_free(redir_lst->next);
		free(redir_lst);
	}
}

static t_redirect	*redir_lst_last(t_redirect *lst)
{
	t_redirect	*last;

	last = NULL;
	if (lst)
	{
		last = lst;
		while (last->next)
			last = last->next;
	}
	return (last);
}

t_redirect	*redir_lst_new(unsigned int redir_type, char *redir_name)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->redir_type = redir_type;
	new->redir_name = redir_name;
	new->next = 0;
	return (new);
}

void	redir_lst_add_back(t_redirect **cmd_lst, t_redirect *new)
{
	t_redirect	*last;

	if (*cmd_lst)
	{
		last = redir_lst_last(*cmd_lst);
		last->next = new;
	}
	else
		*cmd_lst = new;
}
