/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:43:40 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/26 13:07:36 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(t_env *env, char *s)
{
	t_node_env	*aux;

	set_exec(env, ft_strdup("built-ins/unset", NO));
	if (env->size == 0)
		return (1);
	env->size -= 1;
	aux = env->first;
	while (ft_strcmp(aux->data, s) && aux->next)
		aux = (aux->next);
	if (ft_strcmp(aux->data, s) && aux->next)
		return (1);
	if (aux->prev && env->size != 0)
		aux->prev->next = aux->next;
	if (aux->next && env->size != 0)
		aux->next->prev = aux->prev;
	if (env->last == aux)
		env->last = aux->prev;
	if (env->first == aux)
		env->first = aux->next;
	free(aux->data);
	free(aux->value);
	free(aux);
	return (0);
}
