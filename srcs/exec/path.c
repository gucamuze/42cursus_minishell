/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:10:21 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/16 00:13:07 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
