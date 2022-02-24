/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:44:49 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/24 17:19:44 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gets value of ENV variable given in argument. 
// Returns a pointer to it if found, NULL if not
// CAREFUL: The returned pointer is a pointer to the actual env var, no memory
// is allocated !!
char	*get_env_val(char **env, const char *var_name)
{
	size_t	var_len;

	var_len = ft_strlen(var_name);
	while (*env)
	{
		if (ft_strnstr(*env, var_name, var_len))
			return ((*env) + var_len + 1);
		env++;
	}
	return (NULL);
}
