/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:10:24 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 22:09:08 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*iterator;

	if (!*lst)
		return ;
	while (*lst)
	{
		iterator = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = iterator;
	}
	*lst = 0;
}
