/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/23 19:03:33 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_command(char **env, char *command)
{
	char	**cmd_array;
	char	*exe_path;

	cmd_array = ft_split2(command, ' ');
	exe_path = ft_strjoin("/usr/bin/", cmd_array[0]);
	free(cmd_array[0]);
	cmd_array[0] = ft_strdup("minishell");
	if (!fork())
		execve(exe_path, cmd_array, env);

	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*user_input;
	char	*prompt;

	(void)ac;
	(void)av;
	if (!env[0])
		return (0);
	prompt = get_prompt(env, 0);
	if (!prompt)
		return (0);
	while (1)
	{
		user_input = readline(prompt);
		if (!user_input)
			break ;
		printf("user input => %s, c[0] = %d\n", user_input, (int)user_input[0]);
		if (user_input[0] != 0)
			test_command(env, user_input);
		prompt = get_prompt(env, prompt);
		if (!prompt)
			return (0);
	}
	free(prompt);
	return (1);
}
