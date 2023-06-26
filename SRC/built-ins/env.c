/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/26 15:02:25 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_env *env)
{
	t_node_env	*aux;

	set_exec(env, ft_strdup("built-ins/env", NO));
	aux = env->first;
	while (aux)
	{
		if (aux->value)
			printf("%s=%s\n", aux->data, aux->value);
		aux = aux->next;
	}
	return (0);
}

void	create_env(t_env *env, char **splited)
{
	t_node_env	*aux;

	aux = malloc(sizeof(t_node_env));
	if (!aux)
		return ;
	aux->data = splited[0];
	aux->value = splited[1];
	if (env->size == 0)
	{
		env->first = aux;
		env->last = aux;
		aux->prev = NULL;
		aux->next = NULL;
	}
	else
	{
		env->last->next = aux;
		aux->prev = env->last;
		aux->next = NULL;
		env->last = aux;
	}
	env->size += 1;
}

void	check_shlvl(t_env *env)
{
	int	lvl;

	if (exist_env(env, "SHLVL"))
	{
		create_env(env, ft_split("SHLVL=1", '='));
		return ;
	}
	if (search_env(env, "SHLVL"))
		lvl = atoi(search_env(env, "SHLVL"));
	else
		lvl = 0;
	if (lvl < 0)
		lvl = -1;
	if (lvl >= 1000)
	{
		new_err("warning: shell level (", ft_itoa(lvl + 1), \
				") too high, resetting to 1");
		while (lvl >= 999)
			lvl -= 1000;
	}
	mod_env(env, "SHLVL", ft_itoa(lvl + 1));
}

void	init_env(t_mini *mini, char **env)
{
	char	**splited;
	int		i;

	i = 0;
	mini->env = malloc(sizeof(t_env));
	if (!mini->env)
		return ;
	mini->env->size = 0;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		create_env(mini->env, splited);
		i++;
		free(splited);
	}
	if (exist_env(mini->env, "OLDPWD"))
		create_env(mini->env, ft_split("OLDPWD=si", '='));
	mod_env(mini->env, "OLDPWD", NULL);
	check_shlvl(mini->env);
}
