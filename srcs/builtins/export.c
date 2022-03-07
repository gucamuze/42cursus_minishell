/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:51:34 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/07 16:53:12 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	export(t_list **env, const char *str)
// {
// 	char	*var_name;
// 	char	**split;

// 	split = ft_split(str, ' ');
// 	while (*split)
// 	{
// 		var_name = get_env_name_from_string(*split);
// 		while (*env)
// 		{
// 			if (!ft_strncmp(var_name, (*env)->content, ft_strlen(var_name)))
// 				update_env(*env, var_name, &str[ft_strlen(var_name) + 1]);
// 		}
// 		if (var_name)
// 			free(var_name);
// 		split++;
// 	}
// 	free_split(split);
// 	return (0);
// }
