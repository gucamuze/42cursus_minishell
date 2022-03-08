/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/08 15:52:52 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_dispatcher(t_env *env, char *command)
{
	t_command		*cmd;
	unsigned int	return_value;

	cmd = cmd_create(env, command);
	__DEBUG_output_cmd(cmd);
	return_value = -1;
	if (!ft_strncmp(cmd->command, "cd", 2))
		return_value = _cd(cmd);
	else if (!ft_strncmp(cmd->command, "pwd", 3))
		return_value = _pwd(cmd);
	else if (!ft_strncmp(cmd->command, "env", 3))
		return_value = _env(cmd);
	else if (!ft_strncmp(cmd->command, "unset", 5))
		return_value = _unset(cmd);
	else if (!ft_strncmp(cmd->command, "export", 5))
		return_value = _export(cmd);
	else if (!ft_strncmp(cmd->command, "echo", 4))
		return_value = _echo(cmd);
	else if (!ft_strncmp(cmd->command, "exit", 4))
		; // exit
	else
		; // execve
	cmd_free(cmd);
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
