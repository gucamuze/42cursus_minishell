/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:24:53 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/14 18:39:01 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	count_pipes(const char *user_input)
{
	unsigned int	pipes_nbr;

	pipes_nbr = 0;
	while (*user_input)
	{
		if (*user_input++ == '|')
			pipes_nbr++;
	}
	return (pipes_nbr);
}

static unsigned int	str_is_empty(char *str)
{
	while (*str)
		if (*str++ != ' ')
			return (0);
	return (1);
}

static unsigned int	check_empty_pipes(char **input_split, unsigned int pipes_nbr)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (input_split[i])
	{
		if (str_is_empty(input_split[i++]))
			return (1);
		else
			count++;
	}
	if (count != pipes_nbr + 1)
		return (1);
	return (0);
}

char	**cmd_parse_pipes(const char *user_input)
{
	unsigned int	pipes_nbr;
	char			**input_split;

	pipes_nbr = count_pipes(user_input);
	input_split = ft_split(user_input, '|');
	if (check_empty_pipes(input_split, pipes_nbr))
	{
		free_split(input_split);
		return (0);
	}
	return (input_split);
}

t_command	*cmd_lst_create(t_env *env, const char *user_input)
{
	t_command	*cmd_lst;
	char		**split;
	size_t		i;
	
	split = cmd_parse_pipes(user_input);
	if (!split)
	{
		printf("Parsing error: empty pipe detected !\n");
		return (0);
	}
	i = 0;
	cmd_lst = 0;
	while (split[i])
		cmdlst_add_back(&cmd_lst, cmdlst_new(env, split[i++]));
	free_split(split);
	return (cmd_lst);
}
