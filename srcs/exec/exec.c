/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:50:32 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/07 09:41:42 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_paths(const char *command, const char *paths, char **abs_p)
{
	char			**paths_split;
	unsigned int	i;

	paths_split = ft_split(paths, ':');
	i = -1;
	while (paths_split[++i])
	{
		*abs_p = ft_strjoin3(paths_split[i], "/", command);
		if (!access(*abs_p, F_OK))
		{
			free_split(paths_split);
			return (1);
		}
		free(*abs_p);
	}
	free_split(paths_split);
	return (-1);
}

int	get_absolute_path(const char *command, const char *paths, char **abs_p)
{
	if (!access(command, F_OK))
	{
		*abs_p = ft_strdup(command);
		return (1);
	}
	if (paths)
		return (try_paths(command, paths, abs_p));
	return (-1);
}

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
		return (_error("execve", -1));
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
	else if (pid == 0)
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
	char	**envp;
	char	*path;

	if (pipe(cmd->fds) == -1)
		return (-1);
	if (!setup_input_redir(cmd) || !setup_output_redir(cmd))
		return (-1);
	envp = envlst_to_tab(cmd->env);
	if (!envp)
		return (-1);
	if (is_builtin(cmd->command))
		fork_it(cmd->command, cmd, envp, data);
	else
	{
		if (get_absolute_path(cmd->command,
				get_env_val(cmd->env, "PATH", 0), &path) == -1)
		{
			free_split(envp);
			return (_exit_err(": command not found", cmd, 127, -1));
		}
		fork_it(path, cmd, envp, data);
		free(path);
	}
	free_split(envp);
	return (0);
}
