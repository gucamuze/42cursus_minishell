/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:50:32 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/31 22:49:08 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_absolute_path(const char *command, const char *paths)
{
	char			**paths_split;
	char			*absolute_path;
	unsigned int	i;

	paths_split = ft_split(paths, ':');
	// __DEBUG_output_split(paths_split);
	absolute_path = 0;
	i = 0;
	while (paths_split[i])
	{
		absolute_path = ft_strjoin3(paths_split[i], "/", command);
		if (!access(absolute_path, F_OK))
		{
			free_split(paths_split);
			return (absolute_path);
		}
		free(absolute_path);
		i++;
	}
	return (0);
}

static int	fork_it(const char *exec_name, t_command *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (_error("fork error !", 0));
	else if (pid == 0)
	{
		close(cmd->fds[0]);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fds[1], STDOUT_FILENO);
			// return (_error("dup2 error !", -1));
		if (execve(exec_name, cmd->args, envp) == -1)
			return (_error("", -1));
	}
	else
	{
		close(cmd->fds[1]);
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		if (!cmd->next)
			close(cmd->fds[0]);
		cmd->pid = pid;
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
		return (-1); // should close the pipe fd
	envp = envlst_to_tab(cmd->env);
	if (!envp)
		return (-1);
	if (is_builtin(cmd->command))
		exec_builtin(cmd);
	else if (!access(cmd->command, F_OK))
		fork_it(cmd->command, cmd, envp);
	else
	{
		path = get_absolute_path(cmd->command, get_env_val(cmd->env, "PATH"));
		if (!path)
			return (printf("command not found: %s\n", cmd->command));
		fork_it(path, cmd, envp);
		free(path);
	}
	free_split(envp);
	return (0);
}