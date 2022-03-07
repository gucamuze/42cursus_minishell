/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/07 17:37:46 by gucamuze         ###   ########.fr       */
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

// Env
typedef struct s_env
{
	struct s_env	*next;
	char			*name;
	char			*value;
}	t_env;

typedef struct s_command
{
	char				*command;
	char				**args;
	t_env				*env;
	// Token is to potentially expand to a redirect. 
	// Default value is 0 (nothing)
	int					token;
	struct s_command	*next;
}	t_command;

// Future struct to use for free in case of an unexpected exit or sigdie 
typedef struct s_data
{
	t_env	**env;
}		t_data;

// BUILTINS
// cd
int		cd(t_command *cmd);
// echo
void	echo(t_env *env, char *str);
// pwd
int		pwd(t_command *cmd);
// env
int		env(t_command *cmd);
// unset
int		unset(t_command *cmd);
// export
void	export(t_env **env, const char *str);
// END BUILTINS

// UTILS
// env_lst_utils
t_env	*envlst_new(char *var_name, char *var_value);
void	envlst_add_back(t_env **env, t_env *new);
// command_utils
void			cmd_free(t_command *cmd);
t_command		*cmd_create(t_env *env, char *user_input);
void			__DEBUG_output_cmd(t_command *cmd);
// env_utils
unsigned int	expand_env_var(t_env *env, char *var, char **expanded);
t_env	*env_to_lst(char **env);
void	update_env(t_env *env, char *var_name, char *value);
char	*get_env_val(t_env *env, const char *var_name);
void	print_env(t_env *env);
// END UTILS

// prompt
char	*get_prompt(t_env *env, char *prev_prompt);
// signals
void	set_sigaction(struct sigaction *sigaction);
// ft_split
void	free_split(char **split);
char	**ft_split2(const char *s, char c);
// utils
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char	*ft_strncpy(char *str, size_t size);

#endif