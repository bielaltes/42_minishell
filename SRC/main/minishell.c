/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/02 01:36:03 by jsebasti         ###   ########.fr       */
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
	mini.def_env = env;
	g_sig.exit = 0;
	while (g_sig.exit == 0)
	{
		set_signals();
		mini.cmdline = readline("😇 Macroshell ~ ");
		add_history(mini.cmdline);
		lexer(&mini);
		syntax(&mini);
		//expand(cmd_line);
		exec(&mini);
	}
	return (0);
}
