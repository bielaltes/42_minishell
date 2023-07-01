/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:56 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 11:01:01 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **envp, char *exe)
{
	char	**paths;

	while (envp && *envp && ft_strncmp(*envp, "PATH=", 4))
		++envp;
	if (!envp || !(*envp))
	{
		paths = malloc(sizeof(char *) * 2);
		if (!paths)
			end(2, MINI, "malloc", MALLOCER);
		paths[0] = ft_strdup(".", NO);
		paths[1] = NULL;
	}
	else
	{
		if (ft_strchr(exe, '/'))
		{
			*envp = ft_strjoin(*envp, ":.", FIRST);
			if (!envp)
				end(2, MINI, "malloc", MALLOCER);
		}
		paths = ft_split(*envp + 5, ':');
		if (!paths)
			end(2, MINI, "malloc", MALLOCER);
	}
	return (paths);
}

void	free_cnf(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

static char	*get_path_while(char **paths, char *exe)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(*paths, "/", NO);
	if (!tmp)
		end(2, MINI, "malloc", MALLOCER);
	path = ft_strjoin(tmp, exe, NO);
	if (!path)
		end(2, MINI, "malloc", MALLOCER);
	if (ft_strchr(exe, '/') == exe)
		path = exe;
	free(tmp);
	if (access(path, X_OK) == 0)
		return (path);
	else if (access(path, F_OK) == 0)
		end(126, MINI, exe, PERM);
	if (ft_strchr(exe, '/') != exe)
		free(path);
	return (NULL);
}

char	*get_path(char **envp, char *exe, char **envstr)
{
	char	**paths;
	char	**free_aux;

	if (!exe)
		exit(0);
	if (ft_strlen(exe) == 0)
		end(127, MINI, exe, CNF);
	paths = get_paths(envp, exe);
	free_aux = paths;
	while (paths && *paths)
	{
		if (get_path_while(paths, exe))
			return (get_path_while(paths, exe));
		paths++;
	}
	if (ft_strchr(exe, '/') == NULL)
	{
		free_cnf(free_aux);
		free_cnf(envstr);
		end(127, MINI, exe, CNF);
	}
	else
		end(127, MINI, exe, NFILEDIR);
	return (NULL);
}
