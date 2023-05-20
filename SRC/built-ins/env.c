/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/20 05:15:22 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(t_env *env)
{
	int	n_nodes;

	n_nodes = 0;
	while (env->next)
	{
		n_nodes++;
		env = env->next;
	}
	if (env)
		n_nodes++;
	search_env(&env, "go back", 2);
	return (n_nodes);
}

// char	**env_to_str(t_env *env)
// {
// 	int		i;
// 	char	**new;

// 	search_env(env, "go back", 2);
// 	new = malloc(sizeof(char *) * (count_env(env) + 1));
// 	if (!new)
// 		return (NULL);
// 	i = 0;
// 	while(i <= count_env(env))
// 	{
// 		new[i] = ft_strdup(env->data);
// 		env = env->next;
// 		i++;
// 	}

// }

int	exec_env(t_env *env)
{
	while (env->next)
	{
		printf("%s\n", env->data);
		env = env->next;
	}
	printf("%s\n", env->data);
	while (env->prev)
		env = env->prev;
	return (0);
}

void	init_env(t_mini *mini, char **env)
{
	t_env	*aux;
	int		i;

	i = 0;
	aux = malloc(sizeof(t_env));
	if (!aux)
		return ;
	while (env[i])
	{
		mini->env = malloc(sizeof(t_env));
		if (!mini->env)
			return ;
		mini->env->data = ft_strdup(env[i]);
		if (i >= 1)
		{
			aux->next = mini->env;
			mini->env->prev = aux;
		}
		aux = mini->env;
		if (env[i + 1])
			mini->env = mini->env->next;
		i++;
	}
	while (mini->env->prev)
		mini->env = mini->env->prev;
}
