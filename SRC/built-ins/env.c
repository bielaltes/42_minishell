/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:17:21 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/01 20:22:40 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_env *env, const char *s)
{
	char	*var;

	if (search_env(&env, s, 1))
		return (NULL);
	var = env->value;
	search_env(&env, s, 2);
	return (var);
}

int	search_env(t_env **env, const char *s, int opt)
{
	if (opt == 1)
	{
		while (ft_strcmp((*env)->data, s) && (*env)->next)
			(*env) = (*env)->next;
		if (ft_strcmp((*env)->data, s) && !(*env)->next)
			return (1);
		else
			return (0);
	}
	if (opt == 2)
	{
		while ((*env)->prev)
			(*env) = (*env)->prev;
		return (0);
	}
	return (2);
}

int	count_env(t_env *env)
{
	int	n_nodes;

	n_nodes = 0;
	while (env && env->next)
	{
		n_nodes++;
		env = env->next;
	}
	if (env)
		n_nodes++;
	search_env(&env, "go back", 2);
	return (n_nodes);
}

char	**env_to_str(t_env *env)
{
	int		i;
	char	**new;

	search_env(&env, "go back", 2);
	new = malloc(sizeof(char *) * (count_env(env) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while(env && env->next)
	{
		if (env->value)
			new[i] = ft_strjoin(env->data, env->value);
		else
			new[i] = ft_strdup(env->data);
		env = env->next;
		i++;
	}
	if (env->value)
		new[i] = ft_strjoin(env->data, env->value);
	else
		new[i] = ft_strdup(env->data);
	new[i + 1] = NULL;
	return (new);
}

int	exec_env(t_env *env)
{
	search_env(&env, "go back", 2);
	while (env->next)
	{
		if (env->value)
			printf("%s=%s\n", env->data, env->value);
		env = env->next;
	}
	if (env->value)
		printf("%s=%s\n", env->data, env->value);
	while (env->prev)
		env = env->prev;
	return (0);
}

void	init_env(t_mini *mini, char **env)
{
	t_env	*aux;
	char	**splited;
	int		i;

	i = 0;
	aux = malloc(sizeof(t_env));
	if (!aux)
		return ;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		mini->env = malloc(sizeof(t_env));
		if (!mini->env)
			return ;
		mini->env->data = ft_strdup(splited[0]);
		mini->env->value = ft_strdup(splited[1]);
		if (i >= 1)
		{
			aux->next = mini->env;
			mini->env->prev = aux;
		}
		aux = mini->env;
		if (env[i + 1])
			mini->env = mini->env->next;
		i++;
		free(splited);
	}
	while (mini->env->prev)
		mini->env = mini->env->prev;
}
