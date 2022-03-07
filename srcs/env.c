/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:30:56 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/07 12:49:14 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int expand_env_var(t_env *env, char *var, char **expanded)
{
	int		k;
	char	*tmp;

	// printf("expand env var\n");
	k = 0;
	if (var[1] == '?')
		; // last exit code
	else
	{
		while (var[++k] && ft_isalpha(var[k]))
			;
		tmp = ft_strncpy(&var[1], k - 1);
		*expanded = get_env_val(env, tmp);
		// printf("copying '%s' for %d char\ntmp = %s\texpanded => %s\n", var, k, tmp, *expanded);
		free(tmp);
	}
	return (k);
}

char	*get_env_name_from_string(char *str)
{
	char	*env_name;
	unsigned int	i;

	i = 0;
	env_name = NULL;
	while (str[i])
	{
		if (str[i] == '=')
		{
			env_name = malloc(i + 1);
			if (env_name)
			{
				ft_memcpy(env_name, str, i);
				env_name[i] = 0;
			}
			break ;	
		}
		i++;
	}
	return (env_name);
}

t_env	*env_to_lst(char **env)
{
	t_env	*lst;
	char	*var_name;
	char	*var_value;
	
	lst = NULL;
	if (env)
	{
		while (*env)
		{
			var_name = get_env_name_from_string(*env);
			var_value = ft_strdup(&(*env)[ft_strlen(var_name) + 1]);
			envlst_add_back(&lst, envlst_new(var_name, var_value));
			// printf("adding [%s]=[%s] to lst\n", var_name, var_value);
			env++;
		}
	}
	return (lst);
}

// int	export(t_list **env, const char *str)
// {
// 	char	*var_name;
// 	char	**split;

// 	split = ft_split(str, ' ');
// 	while (*split)
// 	{
// 		var_name = get_env_name_from_string(*split);
// 		while (*env)
// 		{
// 			if (!ft_strncmp(var_name, (*env)->content, ft_strlen(var_name)))
// 				update_env(*env, var_name, &str[ft_strlen(var_name) + 1]);
// 		}
// 		if (var_name)
// 			free(var_name);
// 		split++;
// 	}
// 	free_split(split);
// 	return (0);
// }

// NEED TO IMPLEMENT MULTIPLE UNSETS
// from *varn_name to a split ?
void	unset(t_env **env, const char *command)
{
	t_env	*prev;
	t_env	*iterator;
	char	**vars;
	int		i;

	prev = 0;
	vars = ft_split(command, ' ');
	i = -1;
	while (vars[++i])
	{
		iterator = *env;
		while (iterator)
		{
			if (!ft_strncmp(vars[i], iterator->name, ft_strlen(vars[i])))
			{
				if (!prev)
					env = &(iterator)->next;
				else
					prev->next = iterator->next;
				free(iterator);
				break ;			
			}
			prev = iterator;
			iterator = iterator->next;
		}
	}
	free_split(vars);
}

void	print_env(t_env *env)
{
	if (env)
	{
		printf("%s=%s\n", env->name, env->value);
		print_env(env->next);
	}
}

// !! var_name and value MUST BE malloc'd if value is 
// to be created and not updated !!
void	update_env(t_env *env, char *var_name, char *value)
{
	t_env	*iterator;

	iterator = env;
	while (iterator
			&& ft_strncmp(iterator->name, var_name, ft_strlen(var_name)))
		iterator = iterator->next;
	if (iterator)
	{
		free(iterator->value);
		iterator->value = value;
	}
	else
		envlst_add_back(&env, envlst_new(var_name, value));
}

char	*get_env_val(t_env *env, const char *var_name)
{
	size_t	var_len;

	var_len = ft_strlen(var_name);
	while (env)
	{
		if (!ft_strncmp(env->name, var_name, var_len))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
