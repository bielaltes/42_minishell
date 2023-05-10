/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/10 15:57:26 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	array_len(char **arry)
{
	size_t	i;

	i = 0;
	while (arry[i])
		i++;
	return (i);
}

void	init_env(t_mini *mini, char **env)
{
	int	i;

	i = 0;
	mini->env = malloc(sizeof(t_env) * array_len(env));
	/*
	if (!mini->env)
		return ;
	while (env[i])
	{
		mini->env[i].word = env[i];
		printf("%s\n", mini->env[i].word);
		i++;
	}*/
}
