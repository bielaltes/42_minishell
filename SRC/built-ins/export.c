/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/26 13:08:15 by baltes-g         ###   ########.fr       */
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

int	check_args(char **tmp, char *args)
{
	int	i;

	i = -1;
	while (tmp[0][++i])
	{
		if (!ft_isalpha(tmp[0][i]))
		{
			if (ft_strncmp(&tmp[0][i], "_", 1))
			{
				new_err("export: `", args, \
					"': not a valid identifier\n");
				g_sig.ret = 1;
				return (1);
			}
		}
	}
	return (0);
}

int	exec_export(t_env *env, char **args)
{
	char	**tmp;
	int		j;

	j = 1;
	if (!args[1])
		return (print_all_export(env));
	while (args[j])
	{
		tmp = ft_split(args[j], '=');
		if (!check_args(tmp, args[j]))
		{
			if (search_env(env, tmp[0]) && tmp[1])
				mod_env(env, tmp[0], tmp[1]);
			else if (tmp[1])
				create_env(env, tmp);
		}
		free(tmp);
		j++;
	}
	set_exec(env, ft_strdup("built-ins/export", NO));
	return (g_sig.ret);
}
