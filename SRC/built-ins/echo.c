/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/18 09:32:52 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	while (arg[i] == 'n' && arg[i] != '\0')
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}

static void	write_echo(char **args, int *flag, int flag2)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (check_n(args[i]) && *flag == 1 && flag2 == 0)
			i++;
		else if (check_n(args[i]) && *flag == 0 && flag2 == 0)
		{
			*flag = check_n(args[i]);
			i++;
		}
		else
		{
			flag2 = 1;
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
}

int	exec_echo(char **args)
{
	int	i;
	int	flag;
	int	flag2;

	i = 1;
	flag2 = 0;
	flag = 0;
	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	write_echo(args, &flag, flag2);
	if (flag == 0)
		printf("\n");
	return (0);
}
