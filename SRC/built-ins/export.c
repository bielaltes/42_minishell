/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/03 19:42:44 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_all_export(t_env *env)
{
	t_node_env	*aux;

	aux = env->first;
	while (aux)
	{
		if (ft_strcmp(aux->data, "_"))
		{
			if (aux->value)
				printf("declare -x %s=\"%s\"\n", aux->data, aux->value);
			else
				printf("declare -x %s\n", aux->data);
		}
		aux = aux->next;
	}
	return (0);
}

int	exec_export(t_env *env, char *args)
{
	char	**tmp;

	if (!args)
		return (print_all_export(env));
	tmp = ft_split(args, '=');
	if (search_env(env, tmp[0]) && tmp[1])
		mod_env(env, tmp[0], tmp[1]);
	else
		create_env(env, tmp);
	set_exec(env, "built-ins/export");
	return (0);
}
