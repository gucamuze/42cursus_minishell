/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/03 05:45:11 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

typedef struct s_data
{
	char	**env;
}		t_data;

typedef struct s_env
{
	struct s_env	*next;
	char			*name;
	char			*value;
}	t_env;

// env_lst_utils
t_env	*envlst_new(char *var_name, char *var_value);
void	envlst_add_back(t_env **env, t_env *new);
// env
unsigned int	expand_env_var(t_env *env, char *var, char **expanded);
t_env	*env_to_lst(char **env);
void	unset(t_env **env, const char *var_name);
void	export(t_env **env, const char *str);
void	update_env(t_env *env, char *var_name, char *value);
char	*get_env_val(t_env *env, const char *var_name);
void	print_env(t_env *env);
// prompt
char	*get_prompt(t_env *env, char *prev_prompt);
// signals
void	set_sigaction(struct sigaction *sigaction);
// cd
int		cd(t_env *env, char *path);
// echo
void	echo(t_env *env, char *str);
// ft_split
void	free_split(char **split);
char	**ft_split2(const char *s, char c);
// utils
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char	*ft_strncpy(char *str, size_t size);

#endif