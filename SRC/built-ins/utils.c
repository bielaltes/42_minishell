/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:07:05 by jsebasti          #+#    #+#             */
/*   Updated: 2023/07/01 17:19:27 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exec(t_env *env, char *value)
{
	char	*aux;

	aux = ft_strjoin("_=", value, NO);
	if (search_env(env, "_"))
		mod_env(env, "_", value);
	else
		create_env(env, ft_split(aux, '='));
	free(aux);
}

char	**env_to_str(t_env *env)
{
	int			i;
	char		**new;
	t_node_env	*aux;

	aux = env->first;
	if (!aux)
		return (NULL);
	new = malloc(sizeof(char *) * (env->size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (aux)
	{
		if (aux->value)
		{
			new[i] = ft_strjoin(aux->data, "=", NO);
			new[i] = ft_strjoin(new[i], aux->value, FIRST);
		}
		else
			new[i] = ft_strdup(aux->data, NO);
		aux = aux->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	*search_env(t_env *env, const char *s)
{
	t_node_env	*aux;

	aux = env->first;
	if (!aux)
		return (NULL);
	while (ft_strcmp(aux->data, s) && aux->next)
		aux = (aux->next);
	if (ft_strcmp(aux->data, s))
		return (NULL);
	if (aux->value)
		return (ft_strdup(aux->value, NO));
	return (NULL);
}

void	mod_env(t_env *env, const char *s, char *m)
{
	t_node_env	*aux;

	aux = env->first;
	if (!aux)
		return ;
	while (ft_strcmp(aux->data, s) && aux->next)
		aux = (aux->next);
	if (!aux || ft_strcmp(aux->data, s))
		return ;
	if (aux->value)
		free(aux->value);
	aux->value = m;
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
