/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/03 18:01:05 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1 && argv[0])
		exit(1);
	init_env(&mini, env);
	g_sig.exit = 0;
	while (g_sig.exit == 0)
	{
		set_signals();
		mini.cmdline = readline("😇 Macroshell ~ ");
		if (!mini.cmdline)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);	
			break;
		}
		add_history(mini.cmdline);
		lexer(&mini);
		expand(&mini);
		syntax(&mini);
		exec(&mini);
	}
	return (0);
}
