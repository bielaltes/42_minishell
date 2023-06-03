/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/03 18:28:19 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_env *env, const char *s)
{
	char	*var;

	if (search_env(&env, s, 1))
		return (NULL);
	var = env->value;
	search_env(&env, s, 2);
	return (var);
}

int	count_env(t_env *env)
{
	int	n_nodes;

	n_nodes = 0;
	while (env && env->next)
	{
		n_nodes++;
		env = env->next;
	}
	if (env)
		n_nodes++;
	search_env(&env, "go back", 2);
	return (n_nodes);
}

int	exec_env(t_env *env)
{
	search_env(&env, "go back", 2);
	while (env->next)
	{
		if (env->value)
			printf("%s=%s\n", env->data, env->value);
		env = env->next;
	}
	if (env->value)
		printf("%s=%s\n", env->data, env->value);
	while (env->prev)
		env = env->prev;
	set_exec(env, "built-ins/env");
	return (0);
}

void	set_env(t_env **env, char **new, char **splited, int i)
{
	static t_env	*aux;

	if (!aux)
		aux = malloc(sizeof(t_env));
	if (!aux)
		return ;
	(*env)->data = ft_strdup(splited[0]);
	(*env)->value = ft_strdup(splited[1]);
	if (i >= 1)
	{
		aux->next = *env;
		(*env)->prev = aux;
	}
	else
		(*env)->prev = NULL;
	aux = *env;
	if (new[i + 1])
		*env = (*env)->next;
	else
		(*env)->next = NULL;
}

void	init_env(t_mini *mini, char **env)
{
	char	**splited;
	int		i;

	i = 0;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		mini->env = malloc(sizeof(t_env));
		if (!mini->env)
			return ;
		set_env(&mini->env, env, splited, i);
		i++;
		free(splited);
	}
	search_env(&mini->env, "go back", 2);
	if (!search_env(&mini->env, "OLDPWD", 1))
	{
		exec_unset(mini->env, "OLDPWD");
		search_env(&mini->env, "go back", 2);
		exec_export(mini->env, "OLDPWD");
	}
	set_exec(mini->env, "");
}
