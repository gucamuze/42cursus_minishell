/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:16:22 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/08 01:43:23 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**merge_splits(
	char **args, char **split, char **final_split, unsigned int i)
{
	unsigned int	j;
	unsigned int	k;

	j = 0;
	k = 0;
	while (j < i)
	{
		final_split[j] = ft_strdup(args[j]);
		j++;
	}
	while (split[k])
		final_split[j++] = ft_strdup(split[k++]);
	while (args[++i])
		final_split[j++] = ft_strdup(args[i]);
	final_split[j] = 0;
	return (final_split);
}

char	**realloc_if_needed(char **args, unsigned int index)
{
	char			**split;
	char			**final_split;
	unsigned int	i;
	unsigned int	j;

	split = ft_split(args[index], ' ');
	i = 0;
	while (split[i])
		i++;
	if (i <= 1)
	{
		free_split(split);
		return (args);
	}
	j = 0;
	while (args[j])
		j++;
	final_split = malloc((i + j) * sizeof(char *));
	if (!final_split)
		return (args);
	final_split = merge_splits(args, split, final_split, index);
	free_split(args);
	free_split(split);
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
