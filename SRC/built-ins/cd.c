/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/07/01 10:08:59 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(t_env *env, char *s)
{
	char		*tmp;
	char		*aux;
	char		*aux2;

	tmp = NULL;
	aux = ft_strjoin(s, "=", NO);
	if (!aux)
		end(2, MINI, "malloc", MALLOCER);
	tmp = getcwd(tmp, PATH_MAX);
	aux2 = ft_strjoin(aux, tmp, FIRST);
	if (!exist_env(env, s))
		mod_env(env, s, tmp);
	else
		create_env(env, ft_split(aux2, '='));
	free(aux2);
}

static int	option1(t_env *env)
{
	char	*dir;

	dir = malloc(sizeof(char) * PATH_MAX);
	if (!dir)
		end(2, MINI, "malloc", MALLOCER);
	dir = search_env(env, "OLDPWD");
	if (!dir)
	{
		new_err("minishell: cd: ", "OLDPWD", " not set.\n");
		return (1);
	}
	update_oldpwd(env, "OLDPWD");
	chdir(dir);
	update_oldpwd(env, "PWD");
	printf("%s\n", dir);
	free(dir);
	return (0);
}

static int	change_path_o2(t_mini *mini, char *args)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, PATH_MAX);
	if (!dir)
	{
		write(2, "Macroshell: cd: ", 16);
		perror(args);
		return (1);
	}
	if (exist_env(mini->env, "OLDPWD"))
	{
		create_env(mini->env, ft_split(ft_strjoin("OLDPWD=", dir, NO),
				'='));
	}
	if (chdir(args) == -1)
	{
		write(2, "Macroshell: cd: ", 16);
		perror(args);
		return (1);
	}
	mod_env(mini->env, "OLDPWD", dir);
	update_oldpwd(mini->env, "PWD");
	return (0);
}

static int	change_path(t_mini *mini, int option, char *args)
{
	if (option == 0)
	{
		if (exist_env(mini->env, "HOME"))
		{
			new_err("minishell: cd:", "HOME", "not set.\n");
			return (1);
		}
		update_oldpwd(mini->env, "OLDPWD");
		chdir(search_env(mini->env, "HOME"));
		update_oldpwd(mini->env, "PWD");
		return (0);
	}
	if (option == 1)
		return (option1(mini->env));
	if (option == 2)
	{
		return (change_path_o2(mini, args));
	}
	return (1);
}

int	exec_cd(t_mini *mini, char **args)
{
	set_exec(mini->env, ft_strdup("built-ins/cd", NO));
	if (!args[1])
		return (change_path(mini, 0, args[1]));
	if (ft_strlen(args[1]) > PATH_MAX)
		return (1);
	if (!ft_strcmp(args[1], "-"))
		return (change_path(mini, 1, args[1]));
	if (!ft_strcmp(args[1], ""))
		update_oldpwd(mini->env, "OLDPWD");
	else
		return (change_path(mini, 2, args[1]));
	return (0);
}
