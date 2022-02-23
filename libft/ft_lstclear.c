/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:10:24 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/31 23:10:32 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*tmp;

	if (*lst)
	{
		elem = *lst;
		while (elem)
		{
			(*del)(elem->content);
			tmp = elem->next;
			free(elem);
			elem = tmp;
		}
	}
	*lst = NULL;
}
