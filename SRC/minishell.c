/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/07 18:39:36 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_signal(void)
// {
// 	signal();
// }

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.ext = 0;
	init_env(&mini, env);
	if (!mini.env)
		return (1);
	while (mini.ext == 0)
	{
		sleep(5);
		mini.ext = 1;
	}
	free(mini.env);
	return (0);
}
