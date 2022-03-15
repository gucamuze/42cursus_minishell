/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:43:10 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/15 23:14:07 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_absolute_path(char **cmd, t_env *envp);

void	ft_execbuiltin(t_command *cmd_lst)
{
	
	if (ft_strcmp(cmd_lst->command, "cd") == 0)
		_cd(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "pwd") == 0)
		_pwd(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "env") == 0)
		_env(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "unset") == 0)
		_unset(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "export") == 0)
		_export(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "echo") == 0)
		_echo(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "exit") == 0)
		exit(1);
	exit(0);
}

size_t		_lst_size(t_env *command)
{
	t_env *cur;
	size_t	i;

	i = 0;
	cur = command;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

char    **ft_lstsplit(t_env **lst)
{
    char    **res;
    t_env    *ptr;
    int        size;
    int        i;

    ptr = *lst;
    i = -1;
    size = _lst_size(ptr);
    res = (char **)malloc(sizeof(char *) * (size + 1));
    while (++i < size)
    {
        res[i] = ptr->value;
        ptr = ptr->next;
    }
    res[i] = 0;
    return (res);
}

int	havebuiltin(t_command		*cmd_lst)
{
	if (ft_strcmp(cmd_lst->command, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_lst->command, "exit") == 0)
		return (1); // exit
	return (0);
}

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = src[j];
	return (dest);
}

void	exec_cmd(t_command *cmd, char **env, t_env *envt)
{
	char *str;
	
	if (havebuiltin(cmd))
	{
		// printf("exec\n");
		ft_execbuiltin(cmd);
	}
	str = get_absolute_path(cmd->args, envt);
	cmd->args[0] = str;
	if (execve(str, cmd->args, env) == -1)
	{
		// printf("!execve\n");
		perror("shell");
		exit(1);
	}
}


static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

char	*get_absolute_path(char **cmd, t_env *envp)
{
	char	*path = ft_strdup(get_env_val(envp, "PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;

	if (path == NULL) // si le path est null, on cree un path
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	// si cmd n'est pas le chemin absolue, on cherche le chemin absolue du
	// binaire grace a la variable d'environment PATH
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0) {
		// On split le path pour verifier ou ce trouve le binaire
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;

		// On boucle sur chaque dossier du path pour trouver l'emplacement du binaire
		for (int i = 0; path_split[i]; i++) {
			// alloc len du path + '/' + len du binaire + 1 pour le '\0'
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + 1 + ft_strlen(cmd[0]) + 1));
			if (bin == NULL)
				return (cmd[0]) ;

			// On concat le path , le '/' et le nom du binaire
			ft_strcat(bin, path_split[i]);
			ft_strcat(bin, "/");
			ft_strcat(bin, cmd[0]);

			// On verfie l'existence du fichier et on quitte la boucle si access
			// renvoi 0
			if (access(bin, F_OK) == 0)
				return (bin);

			// Nous sommes des gens propre :D
			free(bin);
			bin = NULL;
		}
		free_array(path_split);

		// On remplace le binaire par le path absolue ou NULL si le binaire
		// n'existe pas
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
	return (cmd[0]);
}

size_t		cmdlst_size(t_command *command)
{
	t_command *cur;
	size_t	i;

	i = 0;
	cur = command;
	while (cur)
	{
		i++;
		// printf("%s\n", cur->command);
		cur = cur->next;
	}
	return (i);
}

int *initfd(size_t size)
{
	int *fd;
	size_t i;

	i = 0;
	fd = (int *)malloc (size * sizeof(int) * 2);
	printf("size : %zu\n", size);
	while (i < size)
	{
		pipe(fd + i * 2);
		i++;
	}
	return (fd);
}

void	ft_dup2(int *fd, int i, t_command *command, int size)
{
	int	j;
	
	j = 0;
	if (command->next)
	{
		printf("command = %s\n", command->command);
		if (dup2(fd[i + 1], 1) < 0)
			printf("error\n");
	}
	if (i)
	{
		printf("in i command = %s\n", command->command);
		dup2(fd[i - 2], 0);
	}
	while (j < size * 2)
		close(fd[j++]);
}

void ft_closefd(int *fd)
{
	size_t	i;

	i = 0;
	while (fd[i])
		close(fd[i++]);
}

// for now, command_dispatcher creates the command but this needs to be changed
// in the future, the parser should create the chained list of commands, and 
// send it to the dispatcher
int	command_dispatcher(t_env *env, char *command)
{
	t_command		*cmd_lst;
	unsigned int	return_value;
	int				*fd;
	pid_t			pid;
	int				i;
	int				size;

	cmd_lst = cmd_lst_create(env, command);
	return_value = -1;
	size = cmdlst_size(cmd_lst);
	fd = initfd(size);
	i = 0;
	while (cmd_lst)
	{
		// printf("\ncmd_list w/ pipes :\n");
		// __DEBUG_output_cmd_lst(cmd_lst);
		//if (havebuiltin(cmd_lst) && !cmd_lst->next)
		//	break;
		// printf("command : %s\n", cmd_lst->command);
		pid = fork();
		if (pid == 0)
		{
			ft_dup2(fd, i, cmd_lst, size);
			//checker redirection
			exec_cmd(cmd_lst, ft_lstsplit(&env), env);
		}
		i += 2;
		cmd_lst = cmd_lst->next;
	}
	ft_closefd(fd);
	cmd_lst_free(cmd_lst);
	return (return_value);
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

int	main(int ac, char **av, char **env)
{
	char				*user_input;
	char				*prompt;
	int					status;
	struct sigaction	sa;
	t_env				*env_lst;

	(void)ac;
	(void)av;
	if (!env[0])
		return (0);
	env_lst = env_to_lst(env);
	set_sigaction(&sa);
	prompt = get_prompt(env_lst, 0);
	if (!prompt)
		return (0);
	while (1)
	{
		user_input = readline(prompt);
		if (!user_input)
			break ;
		if (user_input[0] != 0)
		{
			command_dispatcher(env_lst, user_input);
			while(waitpid(-1, &status, 0) != -1)
			{
				if (WIFEXITED(status))
					printf("");
			}
		}
		add_history(user_input);
		prompt = get_prompt(env_lst, prompt);
		if (!prompt)
			return (0);
		free(user_input);
	}
	cleanup(prompt, env_lst);
	return (1);
}
