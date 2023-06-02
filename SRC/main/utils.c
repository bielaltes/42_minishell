/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:07:05 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/02 05:29:18 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exec(t_env *env, char *value)
{
	search_env(&env, "go back", 2);
	if (!search_env(&env, "_", 1))
		env->value = ft_strdup(value);
	else
		exec_export(env, ft_strjoin("_=", value));
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
	while (env && env->next)
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == s2[i] && s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char )s1[i] - (unsigned char )s2[i]);
}
