/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:30:56 by gucamuze          #+#    #+#             */
/*   Updated: 2022/03/03 02:58:18 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *str, size_t size)
{
	char	*cpy;
	int		i;

	cpy = malloc(size + 1);
	if (!cpy)
		return (0);
	i = -1;
	while (str[++i] && size--)
		cpy[i] = str[i];
	cpy[i] = 0;
	// printf("cpy done => %s\n", cpy);
	return (cpy);
}

unsigned int expand_env_var(t_list *env, char *var, char **expanded)
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

t_list	*env_to_lst(char **env)
{
	t_list	*lst;
	
	lst = NULL;
	if (env)
		while (*env)
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(*env++)));
	return (lst);
}

void	unset(t_list **env, const char *var_name)
{
	t_list	*prev;

	prev = 0;
	while (*env)
	{
		if (!ft_strncmp(var_name, (*env)->content, ft_strlen(var_name)))
		{
			if (!prev)
				env = &(*env)->next;
			else
				prev->next = (*env)->next;
			free(*env);
			return ;			
		}
		prev = *env;
		*env = (*env)->next;
	}
}

void	print_env(t_list *env)
{
	if (env)
	{
		printf("%s\n", env->content);
		print_env(env->next);
	}
}

void	update_env(t_list *env, char *var_name, char *value)
{
	t_list	*iterator;

	iterator = env;
	while (iterator
			&& ft_strncmp(iterator->content, var_name, ft_strlen(var_name)))
		iterator = iterator->next;
	if (iterator)
	{
		free(iterator->content);
		iterator->content = ft_strjoin3(var_name, "=", value);
	}
	else
		ft_lstadd_back(&env, ft_lstnew(ft_strjoin3(var_name, "=", value)));
	free(value);
}

// CAREFUL: The returned pointer is a pointer to the actual env var, no memory
// is allocated !!
char	*get_env_val(t_list *env, const char *var_name)
{
	size_t	var_len;

	var_len = ft_strlen(var_name);
	while (env)
	{
		if (!ft_strncmp(env->content, var_name, var_len))
			return (env->content + var_len + 1);
		env = env->next;
	}
	return (NULL);
}
