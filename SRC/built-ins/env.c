/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/03 20:11:27 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_env *env)
{
	t_node_env	*aux;

	aux = env->first;
	while (aux)
	{
		if (aux->value)
			printf("%s=%s\n", aux->data, aux->value);
		aux = aux->next;
	}
	set_exec(env, "built-ins/env");
	return (0);
}

void	create_env(t_env *env, char **splited)
{
	t_node_env	*aux;

	aux = malloc(sizeof(t_node_env));
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

void	init_env(t_mini *mini, char **env)
{
	char	**splited;
	int		i;

	i = 0;
	mini->env = malloc(sizeof(t_env));
	mini->env->size = 0;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		create_env(mini->env, splited);
		i++;
		free(splited);
	}
	if (search_env(mini->env, "OLDPWD"))
	{
		exec_unset(mini->env, "OLDPWD");
		exec_export(mini->env, "OLDPWD");
	}
	set_exec(mini->env, "");
}
