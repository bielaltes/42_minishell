/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/20 18:08:03 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_export(t_mini *mini, char *args)
{
	char	*tmp;
	char	*tmp2;
	t_env	*aux;

	tmp = ft_strchr(args, '=');
	if (!tmp)
		return (1);
	tmp2 = ft_strtrim(args, tmp);
	if (!tmp2)
		return (1);
	if (search_env(&mini->env, tmp2, 1))
	{
		aux = mini->env;
		mini->env = mini->env->next;
		aux->next = mini->env;
		mini->env = malloc(sizeof(t_env));
		if (!mini->env)
			return (1);
		mini->env->prev = aux;
	}
	mini->env->data = ft_strjoin(tmp2, tmp);
	if (!mini->env->data)
		return (1);
	search_env(&mini->env, "go_back", 2);
	return (0);	
}
