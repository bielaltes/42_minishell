/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/14 07:23:39 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->data);
		env = env->prev;
	}
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
	aux->data = NULL;
	aux->next = NULL;
	aux->prev = NULL;
	while (env[i])
	{
		mini->env = malloc(sizeof(t_env));
		if (!mini->env)
			return ;
		if (i < 1)
			mini->env->prev = aux;
		mini->env->data = ft_strdup(env[i]);
		aux = mini->env;
		mini->env = mini->env->next;
		if (i >= 1)
			mini->env->prev = aux;
		i++;
	}
}
