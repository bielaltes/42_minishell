/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:43:40 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/25 11:10:47 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(t_env *env, char *arg)
{
	if (search_env(&env, arg, 1))
		return (1);
	env->prev->next = env->next;
	env->next->prev = env->prev;
	free(env);
	return (0);
}