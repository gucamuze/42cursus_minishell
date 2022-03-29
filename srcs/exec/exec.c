/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:50:32 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/29 16:36:01 by gucamuze         ###   ########.fr       */
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
	int		fork_ret;

	if (pipe(cmd->fds) == -1)
		return (-1);
	pid = fork();
	fork_ret = -1;
	if (pid == -1)
		return (printf("fork error !\n"));
	else if (pid == 0)
	{
		setup_input_redir(cmd);
		setup_output_redir(cmd);
		execve(exec_name, cmd->args, envp);
	}
	else
	{
		waitpid(0, &fork_ret, 0);
		close(cmd->fds[1]);
		close(cmd->fds[0]);
	}
	return (fork_ret);
}

int	exec(t_command *cmd)
{
	char	**envp;
	char	*path;
	int		ret;

	envp = envlst_to_tab(cmd->env);
	ret = -1;
	if (!envp)
		return (ret);
	if (is_builtin(cmd->command))
		exec_builtin(cmd);
	else if (!access(cmd->command, F_OK))
		ret = fork_it(cmd->command, cmd, envp);
	else
	{
		path = get_absolute_path(cmd->command, get_env_val(cmd->env, "PATH"));
		if (!path)
			return (printf("command not found: %s\n", cmd->command));
		ret = fork_it(path, cmd, envp);
		free(path);
	}
	free_split(envp);
	return (ret / 256);
}