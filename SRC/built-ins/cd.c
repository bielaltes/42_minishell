/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/20 03:31:55 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_env(t_env *env, const char *s, int opt)
{
	if (opt == 1)
	{
		while (ft_strncmp(env->data, s, ft_strlen(s)) && env->next)
			env = env->next;
		if (ft_strncmp(env->data, s, ft_strlen(s)) && !env->next)
			return (1);
		else
			return (0);
	}
	if (opt == 2)
	{
		while (env->prev)
			env = env->prev;
		return (0);
	}
	return (2);
}

char	*get_env_var(t_env *env, const char *s)
{
	char	*var;

	if (search_env(env, s, 1))
		return (NULL);
	var = ft_strchr(env->data, '=');
	var++;
	search_env(env, s, 2);
	return (var);
}

static int	update_oldpwd(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	getcwd(tmp, PATH_MAX);
	if (search_env(env, "OLDPWD", 1))
		return (1);
	env->data = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	if (!env->data)
		return (1);
	search_env(env, "borrar", 2); 
	return (0);
}

static int	change_path(t_mini *mini, int options)
{
	char	*dir;

	dir = NULL;
	if (options == 0)
	{
		if (update_oldpwd(mini->env))
			return (1);
		if (search_env(mini->env, "HOME", 1))
		{
			perror("cd: HOME not set.");
			exit(1);
		}
		chdir((ft_split(mini->env->data, '='))[1]);
		search_env(mini->env, "borrar", 2);
		search_env(mini->env, "PATH", 1);
		dir = get_env_var(mini->env, "PATH");
		if (!dir)
			return (1);
		printf("%s\n\n\n", dir);
		return(0);
	}
	if (options == 1)
	{
		dir = malloc(sizeof(char) * PATH_MAX);
		if (!dir)
			return (1);
		dir = get_env_var(mini->env, "OLDPWD");
		if (update_oldpwd(mini->env))
			return (1);

	}
	return (1);
}

int	exec_cd(t_mini *mini)
{
	// char	*temp;
	// char	**splited;

	if (!mini->cmds->args[1])
		return (change_path(mini, 0));
	if (!ft_strncmp(mini->cmds->args[1], "-", 1))
		return (change_path(mini, 1));
	return (0);
}