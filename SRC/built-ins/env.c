/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/11 15:32:07 by baltes-g         ###   ########.fr       */
=======
/*   Updated: 2023/05/14 10:09:30 by jsebasti         ###   ########.fr       */
>>>>>>> dev
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_env *env)
{
	while (env->prev)
		env = env->prev;
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
<<<<<<< HEAD
		mini->env->data = env[i];
		mini->env->prev = mini->env;
		mini->env = mini->env->next;
		//printf("%d\n", i);
=======
		mini->env->data = ft_strdup(env[i]);
		if (i >= 1)
		{
			aux->next = mini->env;
			mini->env->prev = aux;
		}
		aux = mini->env;
		if (env[i + 1])
			mini->env = mini->env->next;
>>>>>>> dev
		i++;
	}
}
