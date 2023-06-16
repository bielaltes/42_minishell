/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:56 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/16 11:33:17 by baltes-g         ###   ########.fr       */
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
		paths[0] = ft_strdup(".");
		paths[1] = NULL;
	}
	else
	{
		if (ft_strchr(exe, '/'))
		{
			*envp = ft_strjoin(*envp, ":.");
			if (!envp)
				end(2, MINI, "malloc", MALLOCER);
		}
		paths = ft_split(*envp + 5, ':');
		if (!paths)
			end(2, MINI, "malloc", MALLOCER);
	}
	return (paths);
}

char	*get_path(char **envp, char *exe)
{
	char	**paths;
	char	*path;
	char	*tmp;

	if (!exe)
		exit(0);
	if (ft_strlen(exe) == 0)
		end(127, MINI, exe, CNF);
	paths = get_paths(envp, exe);
	while (paths && *paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			end(2, MINI, "malloc", MALLOCER);
		path = ft_strjoin(tmp, exe);
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
		paths++;
	}
	end(127, MINI, exe, CNF);
	return (NULL);
}
