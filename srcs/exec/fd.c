/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:11:26 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/16 00:19:18 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *initfd(size_t size)
{
	int *fd;
	size_t i;

	i = 0;
	fd = (int *)malloc (size * sizeof(int) * 2);
	// printf("size : %zu\n", size);
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
		// printf("command = %s\n", command->command);
		if (dup2(fd[i + 1], 1) < 0)
			printf("error\n");
	}
	if (i)
	{
		// printf("in i command = %s\n", command->command);
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