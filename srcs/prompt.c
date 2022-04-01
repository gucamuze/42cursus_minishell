/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:22:30 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/01 16:44:29 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Home var set to 1 if it's in the path, else set to 0
static char	*set_prompt(char *pwd, size_t len, int home)
{
	char	*prompt;

	prompt = malloc(len);
	if (!prompt)
		return (0);
	if (home)
	{
		prompt[0] = '~';
		memcpy(&prompt[1], pwd, len - 4);
	}
	else
		memcpy(prompt, pwd, len - 3);
	prompt[len - 3] = '$';
	prompt[len - 2] = ' ';
	prompt[len - 1] = 0;
	return (prompt);
}

char	*get_prompt(t_env *env, char *prev_prompt)
{
	char	*prompt;
	char	*pwd;
	char	*home;

	pwd = getcwd(0, 0);
	home = get_env_val(env, "HOME");
	prompt = 0;
	if (home && !ft_strncmp(pwd, home, ft_strlen(home)))
		prompt = set_prompt(&pwd[ft_strlen(home)],
				ft_strlen(pwd) - ft_strlen(home) + 4, 1);
	else
		prompt = set_prompt(pwd, ft_strlen(pwd) + 3, 0);
	free(pwd);
	if (!prompt)
		return (0);
	if (!prev_prompt || ft_strncmp(prev_prompt, prompt, ft_strlen(prompt)))
	{
		if (prev_prompt)
			free(prev_prompt);
		return (prompt);
	}
	free(prompt);
	return (prev_prompt);
}
