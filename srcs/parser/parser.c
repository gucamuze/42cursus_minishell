/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:28:01 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/08 15:33:56 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int expand_env_var(t_env *env, char *var, char **expanded)
{
	int		k;
	char	*tmp;

	// printf("expand env var\n");
	k = 0;
	if (var[1] == '?')
		; // last exit code
	else
	{
		while (var[++k] && ft_isalpha(var[k]))
			;
		tmp = ft_strncpy(&var[1], k - 1);
		*expanded = get_env_val(env, tmp);
		// printf("copying '%s' for %d char\ntmp = %s\texpanded => %s\n", var, k, tmp, *expanded);
		free(tmp);
	}
	return (k);
}

// static char	*expand(t_env *env, char *str)
// {
// 	char	expanded[2048];
// 	char	*tmp;
// 	int		i;
// 	int		j;
// 	unsigned int	k;

// 	i = 0;
// 	j = 0;
// 	ft_memset(expanded, 0, 2048);
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1])
// 		{
// 			k = expand_env_var(env, &str[i], &tmp);
// 			// printf("expand function done, i + %d\n", k);
// 			if (tmp)
// 				while (*tmp)
// 					expanded[j++] = *tmp++;
// 			i += k;
// 		}
// 		else
// 			expanded[j++] = str[i++];
// 	}
// 	// printf("end, returning dup of %s\n", expanded);
// 	return (ft_strdup(expanded));
// }

// char	**parser(t_env *env, char *command)
// {
	
// }
