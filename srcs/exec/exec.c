/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:50:32 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/08 03:44:35 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_child(
	const char *exec_name, t_command *cmd, char **envp, t_data *data)
{
	set_signals(1);
	close(cmd->fds[0]);
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fds[1], STDOUT_FILENO);
	if (is_builtin(exec_name))
		exec_builtin(cmd, 1, data);
	else if (execve(exec_name, cmd->args, envp) == -1)
	{
		close_all_fds(cmd);
		exit(_error("execve", -1));
	}
	return (0);
}

static void	exec_parent(t_command *cmd, pid_t pid)
{
	cmd->pid = pid;
	set_signals(2);
	close(cmd->fds[1]);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (!cmd->next)
		close(cmd->fds[0]);
}

static int	fork_it(
	const char *exec_name, t_command *cmd, char **envp, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (_error("fork", 0));
	if (pid == 0)
	{
		if (exec_child(exec_name, cmd, envp, data) == -1)
			return (-1);
	}
	else
		exec_parent(cmd, pid);
	return (0);
}

int	exec(t_command *cmd, t_data *data)
{
	char	*path;

	if (pipe(cmd->fds) == -1)
		return (-1);
	if (!setup_input_redir(cmd) || !setup_output_redir(cmd))
		return (close_all_fds(cmd));
	data->envp = envlst_to_tab(cmd->env);
	if (!data->envp)
		return (-1);
	if (is_builtin(cmd->command))
		fork_it(cmd->command, cmd, data->envp, data);
	else
	{
		if (get_absolute_path(cmd->command,
				get_env_val(cmd->env, "PATH", 0), &path) == -1)
		{
			free_split(data->envp);
			return (_exit_err(": command not found", cmd, 127, -1));
		}
		fork_it(path, cmd, data->envp, data);
		free(path);
	}
	free_split(data->envp);
	data->envp = NULL;
	return (0);
}
