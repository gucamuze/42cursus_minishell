/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/06 21:07:50 by malbrand         ###   ########.fr       */
=======
/*   Updated: 2022/04/07 05:53:13 by gucamuze         ###   ########.fr       */
>>>>>>> fca240eea0449f0f62a19ef51836e47605bdc5dd
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

void	cleanup(t_data *data)
{
	t_env	*env_tmp;

	env_tmp = *data->env;
	if (data)
	{
		if (data->prompt)
			free(data->prompt);
		if (data->env && *data->env)
		{
			while (*data->env)
			{
				env_tmp = (*data->env)->next;
				free((*data->env)->name);
				free((*data->env)->value);
				free(*data->env);
				*data->env = env_tmp;
			}
			free(data->env);
		}
		if (data->user_input)
			free(data->user_input);
		free(data);
	}
	rl_clear_history();
}

static void	update_shlvl(t_env *env)
{
	int	shlvl;

	shlvl = ft_atoi(get_env_val(env, "SHLVL", 0));
	shlvl++;
	if (!get_env_val(env, "SHLVL", 0))
		update_env(env, ft_strdup("SHLVL"), ft_itoa(shlvl));
	else
		update_env(env, "SHLVL", ft_itoa(shlvl));
}

static int	shell_loop(t_data *data)
{
	char	*oldprompt;

	while (1)
	{
		data->user_input = readline(data->prompt);
		if (!data->user_input)
			break ;
		if (!str_is_empty(data->user_input))
		{
			oldprompt = data->prompt;
			parse_and_dispatch(data->env, data->user_input, data);
			add_history(data->user_input);
			add_to_persistent_history(data->user_input, *data->env);
			data->prompt = get_prompt(*data->env, oldprompt);
			free(data->user_input);
			if (!data->prompt)
				return (0);
		}
		else
			free(data->user_input);
	}
	return (1);
}

t_data	*setup_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->env = malloc(sizeof(t_env *));
	if (!data->env)
	{
		free(data);
		return (0);
	}
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_data				*data;

	(void)ac;
	(void)av;
	data = setup_data();
	if (!data)
		return (0);
	*data->env = env_to_lst(env);
	update_shlvl(*data->env);
	set_signals(0);
	data->prompt = get_prompt(*data->env, 0);
	if (!data->prompt)
		return (0);
	if (env)
		import_history(*data->env);
	shell_loop(data);
	cleanup(data);
	exit(0);
}
