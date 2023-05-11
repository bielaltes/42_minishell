/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/11 15:32:07 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->data);
		env = env->next;
	}
	return (0);
}

void	init_env(t_mini *mini, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		mini->env = malloc(sizeof(t_env));
		if (!mini->env)
			return ;
		mini->env->data = env[i];
		mini->env->prev = mini->env;
		mini->env = mini->env->next;
		//printf("%d\n", i);
		i++;
	}
	mini->env = NULL;
}
