/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/23 01:56:42 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	option1(t_mini *mini)
{
	char *dir;

	dir = malloc(sizeof(char) * PATH_MAX);
	if (!dir)
		return (1);
	dir = get_env_var(mini->env, "OLDPWD");
	if (update_oldpwd(mini->env, "OLDPWD="))
	{
		printf("cd: OLDPWD not set.\n");
		return (1);
	}
	chdir(dir);
	if (update_oldpwd(mini->env, "PWD="))
		return (1);
	printf("%s\n", dir);
	return (0);
}

static int	option0(t_mini *mini)
{
	char *dir;

	dir = NULL;
	if (update_oldpwd(mini->env, "OLDPWD="))
	{
		dir = getcwd(dir, PATH_MAX);
		if (exec_export(mini, ft_strjoin("OLDPWD=", dir)) == 1)
			return (1);
		free(dir);
	}
	if (search_env(&mini->env, "HOME=", 1))
	{
		printf("cd: HOME not set.\n");
		return (1);
	}
	chdir(get_env_var(mini->env, "HOME"));
	search_env(&mini->env, "borrar", 2);
	if (update_oldpwd(mini->env, "PWD="))
		return (1);
	return(0);
}

static int	change_path(t_mini *mini, int option, char **args)
{
	char	*dir;

	dir = NULL;
	if (option == 0)
		return (option0(mini));
	if (option == 1)
		return (option1(mini));
	if (option == 2)
	{
		if (update_oldpwd(mini->env, "OLDPWD="))
		{
			dir = getcwd(dir, PATH_MAX);
			if (exec_export(mini, ft_strjoin("OLDPWD=", dir)) == 1)
				return (1);
			free(dir);
		}
		if (chdir(args[1]) == -1)
			printf("cd: No such file or directory: %s\n", args[1]);
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