/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/02/24 16:53:22 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

typedef struct s_data
{
	char	**env;
}		t_data;

// getters
char	*get_env_val(char **env, const char *var_name);
// prompt
char	*get_prompt(char **env, char *prev_prompt);
// signals
void	set_sigaction(struct sigaction *sigaction);
// cd
void	cd(char **env, const char *path);
// TBD
char	**ft_split2(const char *s, char c);

#endif