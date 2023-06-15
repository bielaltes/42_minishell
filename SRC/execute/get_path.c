/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:56 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/15 18:39:00 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(int status, char *str1, char *str2, char *str3)
{
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	exit(status);
}

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
				error_exit(2, MINI, "malloc", MALLOCER);
		}
		paths = ft_split(*envp + 5, ':');
		if (!paths)
			error_exit(2, MINI, "malloc", MALLOCER);
	}
	return (paths);
}

char	*get_path(char **envp, char *exe)
{
	char	**paths;
	char	*path;
	char	*tmp;

	if (ft_strlen(exe) == 0)
		error_exit(127, MINI, exe, CNF);
	paths = get_paths(envp, exe);
	while (paths && *paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			error_exit(2, MINI, "malloc", MALLOCER);
		path = ft_strjoin(tmp, exe);
		if (!path)
			error_exit(2, MINI, "malloc", MALLOCER);
		if (ft_strchr(exe, '/') == exe)
			path = exe;
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		else if (access(path, F_OK) == 0)
			error_exit(126, MINI, exe, PERM);
		if (ft_strchr(exe, '/') != exe)
			free(path);
		paths++;
	}
	error_exit(127, MINI, exe, CNF);
	return (NULL);
}
