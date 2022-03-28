/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/26 17:04:24 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

int	command_dispatcher(t_command *command)
{
	if (command && command->command)
	{
		exec(command);
		if (command->next)
			command_dispatcher(command->next);
	}
	return (g_exit);
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

void	update_shlvl(t_env *env)
{
	int	shlvl;

	shlvl = ft_atoi(get_env_val(env, "SHLVL"));
	shlvl++;
	update_env(env, "SHLVL", ft_itoa(shlvl));
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
	update_shlvl(env_lst);
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
	exit (0);
}
