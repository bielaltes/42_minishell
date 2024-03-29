/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:09:50 by jsebasti          #+#    #+#             */
/*   Updated: 2023/07/01 17:30:43 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist_env(t_env *env, const char *s)
{
	t_node_env	*aux;

	aux = env->first;
	if (!aux)
		return (-1);
	while (ft_strcmp(aux->data, s) && aux->next)
		aux = (aux->next);
	if (ft_strcmp(aux->data, s))
		return (-1);
	return (0);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	new_err(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR);
	ft_putstr_fd(s2, STDERR);
	ft_putstr_fd(s3, STDERR);
}

long int	ft_atoll(char *str)
{
	long int	neg;
	long int	sum;

	neg = 1;
	sum = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + *str - 48;
		++str;
	}
	return (sum * neg);
}

int	ft_strlen_mini(char *str)
{
	size_t	len;

	len = 0;
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\r' && *str != '\t')
			++len;
		++str;
	}
	return (len);
}
