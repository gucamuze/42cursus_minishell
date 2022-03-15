/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:12:16 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/16 00:22:02 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		cmdlst_size(t_command *command)
{
	t_command *cur;
	size_t	i;

	i = 0;
	cur = command;
	while (cur)
	{
		i++;
		// printf("%s\n", cur->command);
		cur = cur->next;
	}
	return (i);
}

size_t		_lst_size(t_env *command)
{
	t_env *cur;
	size_t	i;

	i = 0;
	cur = command;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

char    **ft_lstsplit(t_env **lst)
{
    char    **res;
    t_env    *ptr;
    int        size;
    int        i;

    ptr = *lst;
    i = -1;
    size = _lst_size(ptr);
    res = (char **)malloc(sizeof(char *) * (size + 1));
    while (++i < size)
    {
        res[i] = ptr->value;
        ptr = ptr->next;
    }
    res[i] = 0;
    return (res);
}


char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = src[j];
	return (dest);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
