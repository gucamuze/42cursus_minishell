/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:50:32 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/25 18:44:59 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *command)
{
	if (!ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "exit"))
		return (1);
	return (0);
}

char	*get_absolute_path(const char *command, const char *paths)
{
	char			**paths_split;
	char			*absolute_path;
	unsigned int	i;

	paths_split = ft_split(paths, ':');
	absolute_path = 0;
	i = 0;
	while (paths_split[i])
	{
		absolute_path = ft_strjoin3(paths_split[i], "/", command);
		if (!access(absolute_path, F_OK))
		{
			free_split(paths_split);
			printf("exec succesfully found, full path = %s\n", absolute_path);
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

	pid = fork();
	fork_ret = -1;
	__DEBUG_output_split(envp);
	if (pid == -1)
		return (printf("fork error !\n"));
	else if (pid == 0)
	{
		if (is_builtin(cmd->command))
			exec_builtin(cmd);
		else
		{
			printf("coucou from germany\n");
			execve(exec_name, cmd->args, envp);
		}
	}
	else
		waitpid(0, &fork_ret, 0);
	return (fork_ret);
}

// int	test_relative_path()

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
	{
		printf("exec builtin\n");
		ret = fork_it(cmd->command, cmd, envp);
	}
	else if (!access(cmd->command, F_OK))
	{
		printf("relative path match !\n");
		ret = fork_it(cmd->command, cmd, envp);
	}
	else
	{
		path = get_absolute_path(cmd->command, get_env_val(cmd->env, "PATH"));
		if (!path)
			return (printf("command not found: %s\n", cmd->command));
		printf("abs path=> %s\n", path);
		ret = fork_it(path, cmd, envp);
		free(path);
	}
	free_split(envp);
	printf("done, return => %d\n", ret / 256);
	return (ret / 256);
}