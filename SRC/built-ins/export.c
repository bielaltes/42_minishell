/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/01 19:24:21 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_all_export(t_mini *mini)
{
	search_env(&mini->env, "go back", 2);
	while (mini->env->next)
	{
		if (mini->env->value)
			printf("declare -x %s\"%s\"\n", mini->env->data, mini->env->value);
		else
			printf("declare -x %s\n", mini->env->data);
		mini->env = mini->env->next;
	}
	if (mini->env->value)
		printf("declare -x %s\"%s\"\n", mini->env->data, mini->env->value);
	else
		printf("declare -x %s\n", mini->env->data);
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
	printf("-----------sono qui--------------\n\n");
	aux->next = *env;
	(*env)->prev = aux;
	return (0);
}

int	null_val(t_env *env, char *arg)
{
	if (new_env_node(&env))
		return (1);
	env->data = ft_strdup(arg);
	if (!env->data)
		return (1);
	return (0);
}

int	exec_export(t_mini *mini, char *args)
{
	char	**tmp;
	t_env	*aux;

	if (!args)
		return (print_all_export(mini));
	tmp = ft_split(args, '=');
	if (!tmp[1])
		return (null_val(mini->env, args));
	aux = NULL;
	if (search_env(&mini->env, tmp[0], 1))
		if (!new_env_node(&mini->env))
		{
			mini->env->data = ft_strjoin(tmp[0], "=");
			if (!mini->env->data)
				return (1);
		}
	mini->env->value = ft_strdup(tmp[1]);
	if (!mini->env->value)
		return (1);
	search_env(&mini->env, "go back", 2);
	return (0);
}
