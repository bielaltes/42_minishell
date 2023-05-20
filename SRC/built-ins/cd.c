/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/21 01:42:29 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_env *env, const char *s)
{
	char	*var;

	if (search_env(&env, s, 1))
		return (NULL);
	var = ft_strchr(env->data, '=');
	var++;
	search_env(&env, s, 2);
	return (var);
}

static int	update_oldpwd(t_env *env, const char *s)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(tmp, PATH_MAX);
	if (search_env(&env, s, 1))
		return (1);
	env->data = ft_strjoin(s, tmp);
	free(tmp);
	if (!env->data)
		return (1);
	search_env(&env, "go_back", 2); 
	return (0);
}

static int	options(t_mini *mini, int options)
{
	char	*dir;

	dir = NULL;
	if (options == 0)
	{
		if (update_oldpwd(mini->env, "OLDPWD="))
		{
			perror("cd: OLDPWD not set.");
			return (1);
		}
		if (search_env(&mini->env, "HOME=", 1))
		{
			perror("cd: HOME not set.");
			return (1);
		}
		chdir(get_env_var(mini->env, "HOME"));
		search_env(&mini->env, "borrar", 2);
		if (update_oldpwd(mini->env, "PWD="))
			return (1);
		return(0);
	}
	if (options == 1)
	{
		dir = malloc(sizeof(char) * PATH_MAX);
		if (!dir)
			return (1);
		dir = get_env_var(mini->env, "OLDPWD");
		if (update_oldpwd(mini->env, "OLDPWD="))
			return (1);
		chdir(dir);
		if (update_oldpwd(mini->env, "PWD="))
			return (1);
		return (0);
	}
	return (1);
}

static int	change_path(t_mini *mini, int option, char **args)
{
	int		errno;
	char	*dir;

	errno = 0;
	dir = NULL;
	if (option == 0 || option == 1)
		return (options(mini, option));
	if (option == 2)
	{
		if (update_oldpwd(mini->env, "OLDPWD="))
		{
			dir = getcwd(dir, PATH_MAX);
			if (exec_export(mini, ft_strjoin("OLDPWD=", dir)) == 1)
				return (1);
		}
		if (chdir(args[1]) == -1)
		{
			perror("cd");
			strerror(errno);
		}
		if (update_oldpwd(mini->env, "PWD="))
			return (1);
		return (0);
	}
	return (1);
}

int	exec_cd(t_mini *mini, char **args)
{
	if (args[3])
	{
		perror("cd: too many arguments.");
		return (1);
	}
	if (!args[1])
		return (change_path(mini, 0, args));
	if (!ft_strncmp(args[1], "-", 1))
		return (change_path(mini, 1, args));
	else
		return (change_path(mini, 2, args));
	return (0);
}