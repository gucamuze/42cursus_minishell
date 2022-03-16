/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:28:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/15 23:30:26 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the length of the env variable it expanded
unsigned int expand_env_var(t_env *env, char *var, char **expanded)
{
	int		i;
	char	*tmp;

	i = 0;
	if (var[0] == '$')
	{
		if (var[1] == '?')
			; // last exit code
		else
		{
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
static char	*expand(t_env *env, char *str)
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

char	**create_args(t_env *env, const char *user_input)
{
	char			**args;
	char			*expanded_str;
	unsigned int	i;

	if (!user_input)
		return (0);
	i = 1;
	// ???
	args = ft_split(user_input, ' '); // ???
	// ???
	while (args[i])
	{
		expanded_str = expand(env, args[i]);
		if (expanded_str)
		{
			free(args[i]);
			args[i] = expanded_str;
		}
		i++;
	}
	return (args);
}
