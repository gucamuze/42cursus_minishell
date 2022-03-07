/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/07 14:35:00 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_command(t_env *env, char *command)
{
	t_command	*cmd;

	cmd = cmd_create(env, command);
	__DEBUG_output_cmd(cmd);
	if (!ft_strncmp(cmd->command, "cd", 2))
		cd(env, &command[2]);
	else if (!ft_strncmp(cmd->command, "pwd", 3))
		printf("pwd => %s\n", get_env_val(env, "PWD"));
	else if (!ft_strncmp(cmd->command, "env", 3))
		print_env(env);
	else if (!ft_strncmp(cmd->command, "unset", 5))
		unset(&env, &command[5]);
	/** TEMPORARLY DISABLED BECAUSE OF T_ENV UPDATE **/
	// else if (!ft_strncmp(command, "export", 5))
		// ft_lstadd_back(&env, ft_lstnew(ft_strdup(cmd_array[1])));
	/** **/
	else if (!ft_strncmp(cmd->command, "echo", 4))
		echo(env, &command[5]);
	else if (!ft_strncmp(cmd->command, "exit", 4))
		; // exit
	else
		; // execve
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
			test_command(env_lst, user_input);
		add_history(user_input);
		prompt = get_prompt(env_lst, prompt);
		if (!prompt)
			return (0);
	}
	cleanup(prompt, env_lst);
	return (1);
}
