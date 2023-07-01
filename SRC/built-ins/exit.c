/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/07/01 10:17:48 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_while(int i, char *num)
{
	if (ft_isdigit(num[i]))
		i++;
	else if (num[i] == ' ')
	{
		while (num[i] != '\0')
		{
			if (num[i] == ' ')
				++i;
			else
			{
				new_err("macroshell: exit: ", num, \
					": numeric argument required\n");
				exit(255);
			}
		}
	}
	else
	{
		new_err("macroshell: exit: ", num, ": numeric argument required\n");
		exit(255);
	}
	return (i);
}

static int	check_arg(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+' || num[i] == ' ')
		i++;
	if (num[i] == '\0' || !ft_isdigit(num[i]))
	{
		new_err("macroshell: exit: ", num, ": numeric argument required\n");
		exit(255);
	}
	while (num[i])
		i = check_while(i, num);
	return (0);
}

int	exec_exit(t_mini *mini, char **num)
{
	char	*ext;

	ext = NULL;
	if (!num[1])
	{
		g_sig.exit = g_sig.ret;
		exit(g_sig.exit);
	}
	if (num[1] && !check_arg(num[1]))
		ext = num[1];
	while (*ext == '0')
		ext++;
	if (ft_strlen(ext) > 20 \
		|| (ft_strlen(ext) == 19 && ft_strcmp(ext, "9223372036854775807") > 0) \
		|| (ft_strlen(ext) == 20 && ft_strcmp(ext, "-9223372036854775808") > 0))
	{
		new_err("macroshell: exit: ", num[1], ": numeric argument required");
		exit(255);
	}
	g_sig.exit = ft_atoi(ext, NO);
	if (num[2])
		new_err("exit: ", "too many arguments\n", "");
	set_exec(mini->env, "built-ins/exit");
	exit(g_sig.exit);
}
