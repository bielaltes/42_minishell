/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/18 01:07:46 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
