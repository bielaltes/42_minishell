/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:43:40 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/18 09:00:09 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(t_env *env, char **s)
{
	t_node_env	*aux;
	int			i;

	i = 1;
	if (env->size == 0)
		return (1);
	while (s[i])
	{
		env->size -= 1;
		aux = env->first;
		while (ft_strcmp(aux->data, s[i]) && aux->next)
			aux = (aux->next);
		if (ft_strcmp(aux->data, s[i]) && aux->next)
			return (1);
		if (aux->prev && env->size != 0)
			aux->prev->next = aux->next;
		if (aux->next && env->size != 0)
			aux->next->prev = aux->prev;
		if (env->last == aux)
			env->last = aux->prev;
		free(aux);
		i++;
	}
	return (0);
}
