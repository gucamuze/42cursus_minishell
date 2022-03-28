/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:50:32 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/28 19:46:35 by gucamuze         ###   ########.fr       */
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

// int	setup_output_redir(t_redirect *redirects)
// {
// 	int	fd;
	
// 	fd = -1;
// 	while (redirects)
// 	{
// 		if (redirects->redir_type == 0 || redirects->redir_type == 1)
// 		{
// 			if (fd != -1)
// 				close(fd);
// 			if (redirects->redir_type == 0)
// 				fd = open(redirects->redir_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			else
// 				fd = open(redirects->redir_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			printf("matching redir, fd = %d\n", fd);
// 		}
// 		redirects = redirects->next;
// 	}
// 	return (fd);
// }

int	setup_output_redir(t_command *cmd)
{
	int	fd;
	
	fd = -1;
	while (cmd->redirects)
	{
		if (cmd->redirects->redir_type == 0 || cmd->redirects->redir_type == 1)
		{
			if (fd != -1)
				close(fd);
			if (cmd->redirects->redir_type == 0)
				fd = open(cmd->redirects->redir_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(cmd->redirects->redir_name, 02101, 0644);
		}
		cmd->redirects = cmd->redirects->next;
	}
	if (fd > -1)
	{
		close(cmd->fds[1]);
		cmd->fds[1] = fd;
		dup2(cmd->fds[1], STDOUT_FILENO);
	}
	// printf("fcntl ret in setup, fd %d => %d\n", fd, fcntl(fd, F_GETFD));
	return (fd);
}

int	setup_input_redir(t_command *cmd)
{
	int	fd;
	
	fd = -1;
	while (cmd->redirects)
	{
		if (cmd->redirects->redir_type == 2)
		{
			if (fd != -1)
				close(fd);
			fd = open(cmd->redirects->redir_name, O_RDONLY, 0644);
		}
		cmd->redirects = cmd->redirects->next;
	}
	if (fd > -1)
	{
		close(cmd->fds[0]);
		cmd->fds[0] = fd;
		dup2(cmd->fds[0], STDIN_FILENO);
	}
	// printf("fcntl ret in setup, fd %d => %d\n", fd, fcntl(fd, F_GETFD));
	return (fd);
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
		printf("fd0 value => %d\n", cmd->fds[0]);
		printf("fd1 value => %d\n", cmd->fds[1]);
		if (is_builtin(cmd->command))
			exec_builtin(cmd);
		else
			execve(exec_name, cmd->args, envp);
	}
	else
	{
		close(cmd->fds[1]);
		close(cmd->fds[0]);
		waitpid(0, &fork_ret, 0);
	}
	return (fork_ret);
}

unsigned int	close_all_fds(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->fds[0] != -1)
			close(cmd->fds[0]);
		if (cmd->fds[1] != -1)
			close(cmd->fds[1]);
		cmd = cmd->next;
	}
	return (0);
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
	if (is_builtin(cmd->command) || !access(cmd->command, F_OK))
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