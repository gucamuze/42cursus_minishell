/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/03 00:31:29 by gucamuze         ###   ########.fr       */
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

// env
unsigned int expand_env_var(t_list *env, char *var, char **expanded);
t_list	*env_to_lst(char **env);
void	unset(t_list **env, const char *var_name);
void	update_env(t_list *env, char *var_name, char *value);
char	*get_env_val(t_list *env, const char *var_name);
void	print_env(t_list *env);
// prompt
char	*get_prompt(t_list *env, char *prev_prompt);
// signals
void	set_sigaction(struct sigaction *sigaction);
// cd
int		cd(t_list *env, char *path);
// echo
void	echo(t_list *env, char *str);
// TBD
char	**ft_split2(const char *s, char c);
// utils
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);

#endif