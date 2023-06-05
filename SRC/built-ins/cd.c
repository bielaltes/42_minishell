/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/05 02:19:46 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(t_env *env, char *s)
{
	char		*tmp;
	char		*aux;
	char		*aux2;

	tmp = NULL;
	aux = ft_strjoin(s, "=");
	if (!aux)
		return ;
	tmp = getcwd(tmp, PATH_MAX);
	aux2 = ft_strjoin(aux, tmp);
	if (search_env(env, s))
		mod_env(env, s, tmp);
	else
		create_env(env, ft_split(aux2, '='));
}

static int	option1(t_env *env)
{
	char	*dir;

	dir = malloc(sizeof(char) * PATH_MAX);
	if (!dir)
		return (1);
	dir = search_env(env, "OLDPWD");
	if (!dir)
	{
		printf("cd: OLDPWD not set.\n");
		return (1);
	}
	update_oldpwd(env, "OLDPWD");
	chdir(dir);
	update_oldpwd(env, "PWD");
	printf("%s\n", dir);
	free(dir);
	return (0);
}

static int	option0(t_env *env)
{
	update_oldpwd(env, "OLDPWD");
	if (!search_env(env, "HOME"))
	{
		printf("cd: HOME not set.\n");
		return (1);
	}
	chdir(search_env(env, "HOME"));
	update_oldpwd(env, "PWD");
	return (0);
}

static int	change_path(t_mini *mini, int option, char **args)
{
	char	*dir;

	if (option == 0)
		return (option0(mini->env));
	if (option == 1)
		return (option1(mini->env));
	dir = NULL;
	if (option == 2)
	{
		dir = getcwd(dir, PATH_MAX);
		mod_env(mini->env, "OLDPWD", dir);
		if (!search_env(mini->env, "OLDPWD"))
		{
			create_env(mini->env, ft_split(ft_strjoin("OLDPWD=", dir), '='));
			free(dir);
		}
		if (chdir(args[1]) == -1)
			printf("cd: No such file or directory: %s\n", args[1]);
		update_oldpwd(mini->env, "PWD");
		return (0);
	}
	return (1);
}

int	exec_cd(t_mini *mini, char **args)
{
	if (count_args(args) > 2)
	{
		perror("cd: too many arguments.");
		return (1);
	}
	set_exec(mini->env, "built-ins/cd");
	if (!args[1])
		return (change_path(mini, 0, args));
	if (!ft_strcmp(args[1], "-"))
		return (change_path(mini, 1, args));
	else
		return (change_path(mini, 2, args));
	return (0);
}
