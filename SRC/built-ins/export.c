/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/22 23:41:45 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	print_all_export(t_mini *mini)
// {

// }

int	exec_export(t_mini *mini, char *args)
{
	char	*tmp;
	char	*tmp2;
	t_env	*aux;

	// if (!args)
	// 	return (print_all_export(mini));
	tmp = ft_strchr(args, '=');
	if (!tmp)
		return (1);
	tmp++;
	tmp2 = ft_strtrim(args, tmp);
	if (!tmp2)
		return (1);
	aux = NULL;
	if (search_env(&mini->env, tmp2, 1))
	{
		aux = mini->env;
		mini->env = mini->env->next;
		mini->env = malloc(sizeof(t_env));
		if (!mini->env)
			return (1);
		aux->next = mini->env;
		printf("si");
		mini->env->prev = aux;
	}
	mini->env->data = ft_strjoin(tmp2, tmp);
	if (!mini->env->data)
		return (1);
	search_env(&mini->env, "go_back", 2);
	return (0);	
}
