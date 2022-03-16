/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:24:53 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/16 02:08:52 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static unsigned int	count_pipes(const char *user_input)
// {
// 	unsigned int	pipes_nbr;

// 	pipes_nbr = 0;
// 	while (*user_input)
// 	{
// 		if (*user_input++ == '|')
// 			pipes_nbr++;
// 	}
// 	return (pipes_nbr);
// }

// unsigned int	check_empty_pipes(char **input_split, unsigned int pipes_nbr)
// {
// 	unsigned int	i;
// 	unsigned int	count;

// 	i = 0;
// 	count = 0;
// 	while (input_split[i])
// 	{
// 		if (str_is_empty(input_split[i++]))
// 			return (1);
// 		else
// 			count++;
// 	}
// 	if (count != pipes_nbr + 1)
// 		return (1);
// 	return (0);
// }

// char	**cmd_parse_pipes(const char *user_input)
// {
// 	unsigned int	pipes_nbr;
// 	char			**input_split;

// 	pipes_nbr = count_pipes(user_input);
// 	input_split = ft_split(user_input, '|');
// 	if (check_empty_pipes(input_split, pipes_nbr))
// 	{
// 		free_split(input_split);
// 		return (0);
// 	}
// 	return (input_split);
// }

// Transforms parsed_pipes list to t_command list, with the command raw.
// Also frees the t_list 
t_command	*cmd_lst_create(t_env *env, t_list *parsed_pipes)
{
	t_command	*cmd_lst;
	t_list		*free_terator;
	
	cmd_lst = 0;
	while (parsed_pipes)
	{
		cmdlst_add_back(&cmd_lst, cmdlst_new(env, ft_strdup(parsed_pipes->content)));
		free_terator = parsed_pipes->next;
		free(parsed_pipes);
		parsed_pipes = free_terator;
	}
	return (cmd_lst);
}
