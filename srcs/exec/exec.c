/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:50:32 by gucamuze          #+#    #+#             */
/*   Updated: 2022/04/06 16:46:57 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_absolute_path(const char *command, const char *paths, char **abs_p)
{
	char			**paths_split;
	unsigned int	i;

	if (!access(command, F_OK))
	{
		*abs_p = ft_strdup(command);
		return (1);
	}
	if (paths)
	{
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
	}
	return (-1);
}

static int	fork_it(const char *exec_name, t_command *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (_error("fork", 0));
	else if (pid == 0)
	{
		set_signals(1);
		close(cmd->fds[0]);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fds[1], STDOUT_FILENO);
		if (is_builtin(exec_name))
			exec_builtin(cmd, 1);
		else if (execve(exec_name, cmd->args, envp) == -1)
			return (_error("execve", -1));
	}
	else
	{
		cmd->pid = pid;
		set_signals(2);
		close(cmd->fds[1]);
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		if (!cmd->next)
			close(cmd->fds[0]);
	}
	return (0);
}

int	exec(t_command *cmd)
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
		fork_it(cmd->command, cmd, envp);
	else
	{
		if (get_absolute_path(cmd->command, get_env_val(cmd->env, "PATH", 0), &path) == -1)
			return (_exit_err(": command not found", cmd, 127, -1));			
		fork_it(path, cmd, envp);
		free(path);
	}
	free_split(envp);
	return (0);
}