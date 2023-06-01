/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:43:40 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/01 19:41:33 by jsebasti         ###   ########.fr       */
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
	env = NULL;
	search_env(&env, "go back", 2);
	return (0);
}