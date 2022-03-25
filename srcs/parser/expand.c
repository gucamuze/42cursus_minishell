/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 05:14:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/25 17:08:10 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the length of the env variable it expanded
unsigned int expand_env_var(t_env *env, char *var, char **expanded)
{
	int		i;
	char	*tmp;

	i = 0;
	if (var[i++] == '$')
	{
		if (var[i++] == '?')
			*expanded = ft_itoa(g_exit); // last exit code
		else
		{
			i = 0;
			while (var[++i] && ft_isalpha(var[i]))
				;
			tmp = ft_strncpy(&var[1], i - 1);
			*expanded = get_env_val(env, tmp);
			free(tmp);
		}
	}
	else if (var[0] == '~') {
		*expanded = get_env_val(env, "HOME");
		i = 1;
	}
	return (i);
}

// Does not currently expand the $? variable !
char	*expand(t_env *env, char *str)
{
	char			expanded[2048];
	char			*tmp;
	int				i;
	int				j;
	unsigned int	k;

	i = 0;
	j = 0;
	ft_memset(expanded, 0, 2048);
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1]) || str[i] == '~')
		{
			k = expand_env_var(env, &str[i], &tmp);
			if (tmp)
				while (*tmp)
					expanded[j++] = *tmp++;
			i += k;
		}
		else
			expanded[j++] = str[i++];
	}
	return (ft_strdup(expanded));
}