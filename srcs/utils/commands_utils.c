/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:24:53 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/08 00:31:39 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Transforms parsed_pipes list to t_command list, with the raw command.
// Also frees the pipe t_list 
t_command	*cmd_lst_create(t_env *env, t_list *parsed_pipes)
{
	t_command	*cmd_lst;
	t_list		*free_terator;

	cmd_lst = 0;
	while (parsed_pipes)
	{
		cmdlst_add_back(&cmd_lst, cmdlst_new(env,
				ft_strdup(parsed_pipes->content)));
		free_terator = parsed_pipes->next;
		free(parsed_pipes->content);
		free(parsed_pipes);
		parsed_pipes = free_terator;
	}
	return (cmd_lst);
}
