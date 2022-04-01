/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:29 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/01 16:10:48 by gucamuze         ###   ########.fr       */
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
# include <fcntl.h>
# include <unistd.h>

extern int	g_exit;
// Env
typedef struct s_env
{
	struct s_env		*next;
	char				*name;
	char				*value;
}	t_env;

// Redir type : 0 for >, 1 for >>, 2 for <, 3 for heredoc
typedef struct s_redirect
{
	unsigned int		redir_type;
	char				*redir_name;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	int					fds[2];
	int					fd_in;
	pid_t				pid;
	char				*command;
	char				**args;
	t_env				*env;
	t_redirect			*redirects;
	struct s_command	*next;
}	t_command;

// Future struct to use for free in case of an unexpected exit or sigdie 
typedef struct s_data
{
	t_env		**env;
	t_command	*cmd_lst;
}	t_data;

// EXEC
// exec
int				exec(t_command *cmd);
// exec_fd_utils
unsigned int	close_all_fds(t_command *cmd);
int				setup_input_redir(t_command *cmd);
int				setup_output_redir(t_command *cmd);
// END EXEC

// BUILTINS
unsigned int	is_builtin(const char *command);
int				exec_builtin(t_command *cmd, int mode);
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
t_env			*envlst_new(char *var_name, char *var_value);
size_t			envlst_size(t_env *env);
void			envlst_add_back(t_env **env, t_env *new);
// command_utils
void			cmd_lst_free(t_command *cmd);
t_command		*cmd_lst_create(t_env *env, t_list *parsed_pipes);
// __DEBUG
void			__DEBUG_output_cmd_lst(t_command *cmd);
void			__DEBUG_output_split(char **split);
// commands_lst_utils
t_command		*cmdlst_new(t_env *env, char *command);
void			cmdlst_add_back(t_command **cmd_lst, t_command *new);
// redir_lst_utils
void			redir_lst_free(t_redirect *redir_lst);
t_redirect		*redir_lst_new(unsigned int redir_type, char *redir_name);
void			redir_lst_add_back(t_redirect **cmd_lst, t_redirect *new);
// env_utils
char			*get_env_name_from_string(char *str);
char			*get_env_value_from_string(char *str);
unsigned int	expand_env_var(t_env *env, char *var, char **expanded);
char			**envlst_to_tab(t_env *env);
t_env			*env_to_lst(char **env);
void			update_env(t_env *env, char *var_name, char *value);
char			*get_env_val(t_env *env, const char *var_name);
void			print_env(t_env *env, int fd);
// quotes_utils
unsigned int	is_quote(char c);
unsigned int	get_next_quote_pos(char *str);
int				check_unending_quotes(char *command);
// error_handling_utils
int				_error(const char *s, int ret);
int				_exit_err(char *err_msg, char *command, int exit_code, int ret);
// END UTILS

// PARSER
// parser
char			**create_args(t_env *env, const char *user_input);
// parse_quotes
void			parse_quotes(t_command *cmd_lst);
// parse_pipes
int				check_invalid_pipes(t_list *parsed_pipes);
t_list 			*parse_pipes(char *user_input);
// parse_redirects
int				parse_redirects(t_command *cmd_lst);
// parse_redirects_utils
unsigned int	is_valid_redir_char(char c);
char			*get_redirect_name(char *str);
void			update_command(char *str);
// parse_command
unsigned int	parse_commands(t_command *cmd_lst);
// expand
char			*expand(t_env *env, char *str);
// END PARSER

// prompt
char			*get_prompt(t_env *env, char *prev_prompt);
// signals
void			set_sigaction(struct sigaction *sa);
// ft_split
char			*ft_strndup(const char *s, unsigned int n);
void			free_split(char **split);
// utils
unsigned int	str_is_empty(char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char			*ft_strncpy(char *str, size_t size);

#endif