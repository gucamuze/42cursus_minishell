/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/01 17:11:25 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

int	command_dispatcher(t_command *command)
{
	t_command	*cmd;
	
	cmd = command;
	if (command && command->command)
	{
		if (is_builtin(command->command) && !command->next)
			exec_builtin(command, 0);
		else
		{
			while (command && command->command)
			{
				exec(command);
				command = command->next;
			}
			while (cmd)
			{
				waitpid(0, &g_exit, WUNTRACED);
				cmd = cmd->next;
			}
		}
	}
	return (0);
}

void	set_fds(t_command *cmd)
{
	if (cmd)
	{
		cmd->fds[0] = -1;
		cmd->fds[1] = -1;
		cmd->fd_in = -1;
		set_fds(cmd->next);
	}
}

int	parse_and_dispatch(t_env *env, char *user_input)
{
	t_list		*parsed_pipes;
	t_command	*cmd_lst;

	if (!check_unending_quotes(user_input))
		return(!printf("Syntax error: invalid quotes !\n"));
	parsed_pipes = parse_pipes(user_input);
	if (!check_invalid_pipes(parsed_pipes))
		return(!printf("Syntax error: invalid pipe !\n"));
	cmd_lst = cmd_lst_create(env, parsed_pipes);
	if (!parse_redirects(cmd_lst))
		return (!printf("Syntax error: invalid redirect !\n"));
	parse_commands(cmd_lst);
	parse_quotes(cmd_lst);
	// __DEBUG_output_cmd_lst(cmd_lst);
	set_fds(cmd_lst);
	command_dispatcher(cmd_lst);
	close_all_fds(cmd_lst);
	cmd_lst_free(cmd_lst);
	return (1);
}

void	cleanup(char *prompt, t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	if (prompt)
		free(prompt);
	if (env)
	{
		while (env)
		{
			env_tmp = env->next;
			free(env->name);
			free(env->value);
			free(env);
			env = env_tmp;
		}
	}
	rl_clear_history();
}

void	update_shlvl(t_env *env)
{
	int	shlvl;

	shlvl = ft_atoi(get_env_val(env, "SHLVL"));
	shlvl++;
	update_env(env, "SHLVL", ft_itoa(shlvl));
}

int	shell_loop(char *prompt, t_env *env)
{
	char	*user_input;
	
	while (1)
	{
		user_input = readline(prompt);
		if (!user_input)
			break ;
		if (!str_is_empty(user_input))
		{
			parse_and_dispatch(env, user_input);
			add_history(user_input);
			prompt = get_prompt(env, prompt);
			if (!prompt)
				return (0);
		}
		free(user_input);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char				*prompt;
	struct sigaction	sa;
	t_env				*env_lst;

	(void)ac;
	(void)av;
	env_lst = env_to_lst(env);
	update_shlvl(env_lst);
	set_sigaction(&sa);
	prompt = get_prompt(env_lst, 0);
	if (!prompt)
		return (0);
	shell_loop(prompt, env_lst);
	cleanup(prompt, env_lst);
	exit (0);
}
