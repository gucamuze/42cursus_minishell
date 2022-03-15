/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/16 00:18:58 by adben-mc         ###   ########.fr       */
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
	// A implementer
		//char				*redirection;
	// Token is to potentially expand to a redirect. 
	// Default value is 0 (nothing)
	struct s_command	*next;
}	t_command;

// Future struct to use for free in case of an unexpected exit or sigdie 
typedef struct s_data
{
	t_env	**env;
}		t_data;

// BUILTINS
// cd
unsigned int	_cd(t_command *cmd);
// echo
unsigned int	_echo(t_command *cmd);
// pwd
unsigned int	_pwd(t_command *cmd);
// env
unsigned int	_env(t_command *cmd);
// unset
unsigned int	_unset(t_command *cmd);
// export
unsigned int	_export(t_command *cmd);
// exit
// unsigned int	exit();
// END BUILTINS

// UTILS
// env_lst_utils
t_env	*envlst_new(char *var_name, char *var_value);
void	envlst_add_back(t_env **env, t_env *new);
// command_utils
void			cmd_lst_free(t_command *cmd);
t_command		*cmd_lst_create(t_env *env, const char *user_input);
// __DEBUG
void			__DEBUG_output_cmd_lst(t_command *cmd);
void			__DEBUG_output_split(char **split);
// commands_lst_utils
t_command		*cmdlst_new(t_env *env, const char *user_input);
void			cmdlst_add_back(t_command **cmd_lst, t_command *new);
// env_utils
char	*get_env_name_from_string(char *str);
char	*get_env_value_from_string(char *str);
unsigned int	expand_env_var(t_env *env, char *var, char **expanded);
t_env	*env_to_lst(char **env);
void	update_env(t_env *env, char *var_name, char *value);
char	*get_env_val(t_env *env, const char *var_name);
void	print_env(t_env *env);
// END UTILS

// PARSER
// parser
char	**create_args(t_env *env, const char *user_input);

// END PARSER

// prompt
char	*get_prompt(t_env *env, char *prev_prompt);
// signals
void	set_sigaction(struct sigaction *sigaction);
// ft_split
void	free_split(char **split);
char	**ft_split2(const char *s, char c);
// utils
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char	*ft_strncpy(char *str, size_t size);


/******************************************************************************/
/***************************	EXECUTION	***********************************/
//exec
void	ft_execbuiltin(t_command	*cmd_lst);
int		havebuiltin(t_command	*cmd_lst);
void	exec_cmd(t_command *cmd, char **env, t_env *envt);
//fd
int		*initfd(size_t size);
void	ft_dup2(int *fd, int i, t_command *command, int size);
void	ft_closefd(int *fd);
//path
char	*get_absolute_path(char **cmd, t_env *envp);
//utils
void	free_array(char **array);
char	*ft_strcat(char *dest, char *src);
char    **ft_lstsplit(t_env **lst);
size_t	_lst_size(t_env *command);
size_t	cmdlst_size(t_command *command);
/******************************************************************************/

#endif