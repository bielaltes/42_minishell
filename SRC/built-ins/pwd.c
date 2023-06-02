/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/02 01:36:40 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_env *env)
{
	while (ft_strncmp(env->data, "PWD=", 4) && env->next)
		env = env->next;
	printf("%s\n", env->value);
	while (env->prev)
		env = env->prev;
	return (0);
}
