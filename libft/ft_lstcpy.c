/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:30:44 by gucamuze          #+#    #+#             */
/*   Updated: 2022/01/27 17:33:25 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstcpy(t_list *stack)
{
	t_list	*begin;
	t_list	*ptr;

	begin = NULL;
	ptr = NULL;
	if (stack)
		begin = ft_lstnew(stack->content);
	ptr = begin;
	while (stack->next)
	{
		ptr->next = ft_lstnew(stack->next->content);
		ptr = ptr->next;
		stack = stack->next;
	}
	ptr = begin;
	return (begin);
}
