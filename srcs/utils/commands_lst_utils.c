/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_lst_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:13:41 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/07 20:41:22 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// No need to free command as its a pointer to args[0]
void	cmd_lst_free(t_command *cmd_lst)
{
	if (cmd_lst)
	{
		if (cmd_lst->args)
			free_split(cmd_lst->args);
		if (cmd_lst->redirects)
			redir_lst_free(cmd_lst->redirects);
		if (cmd_lst->next)
			cmd_lst_free(cmd_lst->next);
		free(cmd_lst);
	}
}

void	cmd_lst_free_if_error(t_command *cmd_lst)
{
	if (cmd_lst)
	{
		if (cmd_lst->args)
			free_split(cmd_lst->args);
		if (cmd_lst->command)
			free(cmd_lst->command);
		if (cmd_lst->redirects)
			redir_lst_free(cmd_lst->redirects);
		if (cmd_lst->next)
			cmd_lst_free(cmd_lst->next);
		free(cmd_lst);
	}
}

static t_command	*cmdlst_last(t_command *lst)
{
	t_command	*last;

	last = 0;
	if (lst)
	{
		last = lst;
		while (last->next)
			last = last->next;
	}
	return (last);
}

t_command	*cmdlst_new(t_env *env, char *command)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (0);
	new->command = command;
	new->args = 0;
	new->env = env;
	new->redirects = 0;
	new->exit_code = 0;
	new->pid = 0;
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
