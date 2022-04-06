/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:38:16 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 17:01:46 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*command_to_lst(char *str)
{
	t_list			*lst;
	unsigned int	j;

	lst = 0;
	while (*str)
	{
		j = 0;
		while (str[j] && str[j] != ' ')
		{
			if (is_quote(str[j]))
				j += get_next_quote_pos(&str[j]) + 1;
			else
				j++;
		}
		if (j)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(str, j)));
			str += j - 1;
		}
		str++;
	}
	return (lst);
}

static char	**lst_to_args(t_list *lst)
{
	size_t	args_size;
	size_t	i;
	char	**args;

	args_size = ft_lstsize(lst);
	i = 0;
	args = malloc((args_size + 1) * sizeof(char *));
	if (!args)
		return (0);
	while (i < args_size)
	{
		args[i] = lst->content;
		lst = lst->next;
		i++;
	}
	args[i] = 0;
	return (args);
}

static void	free_tmp_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	lst = 0;
}

// After the command is parsed, the args **char is ready, but the command *char 
// isnt set, and will instead be set after parsing quotes
unsigned int	parse_commands(t_command *cmd_lst)
{
	t_list	*lst;

	lst = 0;
	while (cmd_lst)
	{
		lst = command_to_lst(cmd_lst->command);
		cmd_lst->args = lst_to_args(lst);
		if (!cmd_lst->args)
			return (0);
		free(cmd_lst->command);
		free_tmp_lst(lst);
		cmd_lst = cmd_lst->next;
	}
	return (1);
}
