/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:30:11 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/03 00:59:10 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand(t_list *env, char *str)
{
	char	expanded[2048];
	char	*tmp;
	int		i;
	int		j;
	unsigned int	k;

	i = 0;
	j = 0;
	ft_memset(expanded, 0, 2048);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			k = expand_env_var(env, &str[i], &tmp);
			printf("expand function done, i + %d\n", k);
			if (tmp)
				while (*tmp)
					expanded[j++] = *tmp++;
			i += k;
		}
		else
			expanded[j++] = str[i++];
	}
	printf("end, returning dup of %s\n", expanded);
	return (ft_strdup(expanded));
}

void	echo(t_list *env, char *str)
{
	char	**output;
	int		space_flag;
	int		i;

	space_flag = 0;
	output = ft_split2(str, ' ');
	if (!output)
		printf("no output for '%s'", str);
	i = -1;
	if (output[0] && output[0][0] == '-')
	{
		if (output[0][1] == 'n')
			space_flag = 1;
		i++;	
	}
	printf("wtf is going on, string '%s'\n", str);
	while (output[++i])
	{
		char *test = expand(env, output[i]);
		printf("expanding %s => %s", output[i], test);
	}
	if (!space_flag)
		printf("\n");
}