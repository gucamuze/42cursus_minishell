/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:16:22 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 17:17:45 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**merge_splits(char **split1, char **split2, char **final_split)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (split1[i])
		final_split[j++] = ft_strdup(split1[i++]);
	i = 1;
	while (split2[i])
		final_split[j++] = ft_strdup(split2[i++]);
	final_split[j] = 0;
	return (final_split);
}

char	**realloc_if_needed(char **args)
{
	char			**split;
	char			**final_split;
	unsigned int	i;
	unsigned int	j;

	split = ft_split(args[0], ' ');
	i = 0;
	while (split[i])
		i++;
	if (i <= 1)
		return (args);
	j = 1;
	while (args[j])
		j++;
	final_split = malloc((i + j) * sizeof(char *));
	if (!final_split)
		return (args);
	final_split = merge_splits(split, args, final_split);
	free(args);
	free(split);
	return (final_split);
}

void	delete_quotes(char *str)
{
	unsigned int	len;

	if (is_quote(str[0]))
	{
		len = ft_strlen(str) - 1;
		str[len] = 0;
		ft_memmove(str, &str[1], len);
	}
}
