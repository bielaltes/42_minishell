/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/18 17:21:32 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	if (num[i] == '\0' || !ft_isdigit(num[i]))
	{
		new_err("macroshell: exit: ", num, ": numeric argument required\n");
		exit(255);
	}
	while (num[i])
	{
		if (ft_isdigit(num[i]))
			i++;
		else
		{
			new_err("macroshell: exit: ", num, ": numeric argument required\n");
			exit(255);
		}
	}
	return (0);
}

int	exec_exit(t_mini *mini, char **num)
{
	long long	ext;

	ext = 0;
	if (!num[1])
	{
		g_sig.exit = g_sig.ret;
		exit(g_sig.exit);
	}
	if (num[1] && !check_arg(num[1]))
		ext = ft_atoll(num[1]);
	if (ext > LONG_MAX || ext < LONG_MIN)
	{
		new_err("macroshell: exit: ", num[1], ": numeric argument required");
		exit(255);
	}
	if (num[2])
		new_err("exit: ", "too many arguments\n", "");
	g_sig.exit = ext;
	set_exec(mini->env, "built-ins/exit");
	exit(g_sig.exit);
}
