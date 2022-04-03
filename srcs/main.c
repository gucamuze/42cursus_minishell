/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/03 02:47:43 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

void	cleanup(char *prompt, t_env *env, char **history)
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
	if (history)
		free_split(history);
	rl_clear_history();
}

void	update_shlvl(t_env *env)
{
	int	shlvl;

	shlvl = ft_atoi(get_env_val(env, "SHLVL", 0));
	shlvl++;
	if (!get_env_val(env, "SHLVL", 0))
		update_env(env, ft_strdup("SHLVL"), ft_itoa(shlvl));
	else
		update_env(env, "SHLVL", ft_itoa(shlvl));
}

int	shell_loop(char *prompt, t_env *env)
{
	char	*user_input;
	
	while (1)
	{
		user_input = readline(prompt);
		if (!user_input)
			break ;
		if (!str_is_empty(user_input))
		{
			parse_and_dispatch(&env, user_input);
			add_history(user_input);
			add_to_persistent_history(user_input, env);
			prompt = get_prompt(env, prompt);
			free(user_input);
			if (!prompt)
				return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char				*prompt;
	struct sigaction	sa;
	t_env				*env_lst;
	char				**history;

	(void)ac;
	(void)av;
	env_lst = env_to_lst(env);
	update_shlvl(env_lst);
	set_sigaction(&sa, 0);
	prompt = get_prompt(env_lst, 0);
	if (!prompt)
		return (0);
	history = 0;
	if (env)
		import_history(history, env_lst);
	shell_loop(prompt, env_lst);
	cleanup(prompt, env_lst, history);
	exit (0);
}
