/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/24 19:01:16 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_command(t_list *env, char *command)
{
	char	**cmd_array;

	cmd_array = ft_split2(command, ' ');
	if (!ft_strncmp(cmd_array[0], "cd", 2))
	{
		cd(env, cmd_array[1]);
	}
	else if (!ft_strncmp(cmd_array[0], "pwd", 3))
		printf("pwd => %s\n", get_env_val(env, "PWD"));
	else if (!ft_strncmp(cmd_array[0], "pwd", 3))
		printf("pwd => %s\n", get_env_val(env, "PWD"));

	return (1);
}

int	main(int ac, char **av, char **env)
{
	char				*user_input;
	char				*prompt;
	struct sigaction	sa;
	t_list				*env_lst;

	(void)ac;
	(void)av;
	if (!env[0])
		return (0);
	env_lst = env_to_lst(env);
	set_sigaction(&sa);
	prompt = get_prompt(env_lst, 0);
	if (!prompt)
		return (0);
	printf("test=> %s\n", ft_strjoin3("coucou", " ", "toi !"));
	while (1)
	{
		user_input = readline(prompt);
		if (!user_input)
			break ;
		printf("user input => %s, c[0] = %d\n", user_input, (int)user_input[0]);
		if (user_input[0] != 0)
			test_command(env_lst, user_input);
		prompt = get_prompt(env_lst, prompt);
		if (!prompt)
			return (0);
	}
	free(prompt);
	return (1);
}
