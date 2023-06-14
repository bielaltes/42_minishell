/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/12 18:16:20 by jsebasti         ###   ########.fr       */
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
				new_err("export: '", args, \
					"': not a valid identifier\n");
				return (1);
			}
		}
	}
	return (0);
}

int	exec_export(t_env *env, char **args)
{
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!args)
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
	set_exec(env, "built-ins/export");
	return (0);
}
