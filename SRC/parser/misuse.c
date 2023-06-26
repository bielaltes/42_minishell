/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misuse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:15:06 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/26 19:33:35 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_error(char c, char *str)
{
	g_sig.ret = 2;
	ft_printf("Minishell: %c : %s\n", c, str);
	return (1);
}

static int	unsuported(char *c)
{
	if (*c == '(' || *c == ')' || *c == '*' || *c == '\\' || *c == ';')
		return (1);
	else if (*c == '|' && (c + 1) && *(c + 1) == '|')
		return (1);
	else if (*c == '&' && (c + 1) && *(c + 1) == '&')
		return (1);
	return (0);
}

int	misuse(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (unsuported(&cmd[i]))
			return (is_error(cmd[i], "still not implemented"));
		if (cmd[i] == '\'')
		{
			++i;
			while (cmd[i] && cmd[i] != '\'')
				++i;
			if (!cmd[i])
				return (is_error(cmd[i], "dquote not implemented"));
		}
		else if (cmd[i] == '"')
		{
			++i;
			while (cmd[i] && cmd[i] != '"')
				++i;
			if (!cmd[i])
				return (is_error(cmd[i], "dquote not implemented"));
		}
		++i;
	}
	return (0);
}
