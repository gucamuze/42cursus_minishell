/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_lst_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:13:41 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/14 17:32:35 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_lst_free(t_command *cmd_lst)
{
	if (cmd_lst)
	{
		if (cmd_lst->args)
			free_split(cmd_lst->args);
		if (cmd_lst->next)
			cmd_lst_free(cmd_lst->next);
		free(cmd_lst);
	}
}

static t_command	*cmdlst_last(t_command *lst)
{
	t_command	*last;

	last = NULL;
	if (lst)
	{
		last = lst;
		while (last->next)
			last = last->next;
	}
	return (last);
}

t_command	*cmdlst_new(t_env *env, const char *user_input)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->args = create_args(env, user_input);
	if (new->args)
		new->command = new->args[0];
	else
		new->command = 0;
	new->env = env;
	new->next = 0;
	return (new);
}

void	cmdlst_add_back(t_command **cmd_lst, t_command *new)
{
	t_command	*last;
	
	if (*cmd_lst)
	{
		last = cmdlst_last(*cmd_lst);
		last->next = new;
	}
	else
		*cmd_lst = new;
}