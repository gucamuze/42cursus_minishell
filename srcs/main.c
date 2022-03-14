/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/14 18:40:04 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for now, command_dispatcher creates the command but this needs to be changed
// in the future, the parser should create the chained list of commands, and 
// send it to the dispatcher
int	command_dispatcher(t_env *env, char *command)
{
	t_command		*cmd_lst;
	unsigned int	return_value;

	cmd_lst = cmd_lst_create(env, command);
	return_value = -1;
	if (cmd_lst)
	{
		printf("\ncmd_list w/ pipes :\n");
		__DEBUG_output_cmd_lst(cmd_lst);
		if (!ft_strcmp(cmd_lst->command, "cd"))
			return_value = _cd(cmd_lst);
		else if (!ft_strcmp(cmd_lst->command, "pwd"))
			return_value = _pwd(cmd_lst);
		else if (!ft_strcmp(cmd_lst->command, "env"))
			return_value = _env(cmd_lst);
		else if (!ft_strcmp(cmd_lst->command, "unset"))
			return_value = _unset(cmd_lst);
		else if (!ft_strcmp(cmd_lst->command, "export"))
			return_value = _export(cmd_lst);
		else if (!ft_strcmp(cmd_lst->command, "echo"))
			return_value = _echo(cmd_lst);
		else if (!ft_strcmp(cmd_lst->command, "exit"))
			; // exit
		else
			; // execve
	}
	cmd_lst_free(cmd_lst);
	return (return_value);
}

void	cleanup(char *prompt, t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	if (prompt)
		free(prompt);
	if (env)
	{
		while (env)
		{
			env_tmp = env->next;
			free(env->name);
			free(env->value);
			free(env);
			env = env_tmp;
		}
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	char				*user_input;
	char				*prompt;
	struct sigaction	sa;
	t_env				*env_lst;

	(void)ac;
	(void)av;
	if (!env[0])
		return (0);
	env_lst = env_to_lst(env);
	set_sigaction(&sa);
	prompt = get_prompt(env_lst, 0);
	if (!prompt)
		return (0);
	while (1)
	{
		user_input = readline(prompt);
		if (!user_input)
			break ;
		if (user_input[0] != 0)
			command_dispatcher(env_lst, user_input);
		add_history(user_input);
		prompt = get_prompt(env_lst, prompt);
		if (!prompt)
			return (0);
		free(user_input);
	}
	cleanup(prompt, env_lst);
	return (1);
}
