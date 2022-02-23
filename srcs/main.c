/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/23 18:29:35 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("user input => %s\n", user_input);
		prompt = get_prompt(env, prompt);
		if (!prompt)
			return (0);
		if (!user_input)
			break ;
	}
	free(prompt);
	// while (*split)
	// 	printf("split = %s\n", *split++);
	// printf("ret=>%s\n", get_env_val(env, "PATH"));
	return (1);
}
