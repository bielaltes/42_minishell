/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/02 05:56:16 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_all_export(t_env *env)
{
	search_env(&env, "go back", 2);
	while (env->next)
	{
		if (ft_strcmp(env->data, "_"))
		{
			if (env->value)
				printf("declare -x %s=\"%s\"\n", env->data, env->value);
			else
				printf("declare -x %s\n", env->data);
		}
		env = env->next;
	}
	if (ft_strcmp(env->data, "_"))
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->data, env->value);
		else
			printf("declare -x %s\n", env->data);
	}
	return (0);
}

int	new_env_node(t_env **env)
{
	t_env	*aux;

	while ((*env)->next)
		*env = (*env)->next;
	aux = *env;
	*env = (*env)->next;
	*env = malloc(sizeof(t_env));
	if (!*env)
		return (1);
	aux->next = *env;
	(*env)->prev = aux;
	return (0);
}

int	null_val(t_env *env, char *arg)
{
	if (!search_env(&env, arg, 1))
		return (0);
	if (new_env_node(&env))
		return (1);
	env->data = ft_strdup(arg);
	if (!env->data)
		return (1);
	return (0);
}

int	exec_export(t_env *env, char *args)
{
	char	**tmp;
	t_env	*aux;

	if (!args)
		return (print_all_export(env));
	tmp = ft_split(args, '=');
	if (!tmp[1])
		return (null_val(env, tmp[0]));
	aux = NULL;
	if (search_env(&env, tmp[0], 1))
	{
		if (!new_env_node(&env))
		{
			env->data = ft_strdup(tmp[0]);
			if (!env->data)
				return (1);
		}
	}
	env->value = ft_strdup(tmp[1]);
	if (!env->value)
		return (1);
	search_env(&env, "go back", 2);
	set_exec(env, "built-ins/export");
	return (0);
}
