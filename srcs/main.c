/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/17 18:56:36 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for now, command_dispatcher creates the command but this needs to be changed
// in the future, the parser should create the chained list of commands, and 
// send it to the dispatcher
int	command_dispatcher(t_command *command)
{
	unsigned int	return_value;

	return_value = -1;
	if (command && command->command)
	{
		if (!ft_strcmp(command->command, "cd"))
			return_value = _cd(command);
		else if (!ft_strcmp(command->command, "pwd"))
			return_value = _pwd(command);
		else if (!ft_strcmp(command->command, "env"))
			return_value = _env(command);
		else if (!ft_strcmp(command->command, "unset"))
			return_value = _unset(command);
		else if (!ft_strcmp(command->command, "export"))
			return_value = _export(command);
		else if (!ft_strcmp(command->command, "echo"))
			return_value = _echo(command);
		else if (!ft_strcmp(command->command, "exit"))
			; // exitA
		else
			; // execve
		// cmd
	}
	return (return_value);
}

int	parse_and_dispatch(t_env *env, char *user_input)
{
	t_list		*parsed_pipes;
	t_command	*cmd_lst;

	if (!check_unending_quotes(user_input))
		return(!printf("Syntax error: invalid quotes !\n"));
	parsed_pipes = parse_pipes(user_input);
	if (!check_invalid_pipes(parsed_pipes))
		return(!printf("Syntax error: invalid pipe !\n"));
	cmd_lst = cmd_lst_create(env, parsed_pipes);
	if (!parse_redirects(cmd_lst))
		return (!printf("Syntax error: invalid redirect !\n"));
	parse_commands(cmd_lst);
	parse_quotes(cmd_lst);
	__DEBUG_output_cmd_lst(cmd_lst);
	command_dispatcher(cmd_lst);
	cmd_lst_free(cmd_lst);
	return (1);
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
		if (!str_is_empty(user_input))
		{
			parse_and_dispatch(env_lst, user_input);
			// command_dispatcher(env_lst, user_input);
			add_history(user_input);
			prompt = get_prompt(env_lst, prompt);
			if (!prompt)
				return (0);
		}
		free(user_input);
	}
	cleanup(prompt, env_lst);
	return (1);
}
