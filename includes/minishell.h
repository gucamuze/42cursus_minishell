/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/23 17:08:20 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	int	caca;
}		t_data;

// getters
char	*get_env_val(char **env, const char *var_name);
// TBD
char	**ft_split2(const char *s, char c);

#endif