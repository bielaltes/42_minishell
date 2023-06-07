/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:09:50 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/06 10:31:29 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist_env(t_env *env, const char *s)
{
	t_node_env	*aux;

	aux = env->first;
	while (ft_strcmp(aux->data, s) && aux->next)
		aux = (aux->next);
	if (ft_strcmp(aux->data, s))
		return (-1);
	return (0);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
