/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/15 17:36:41 by baltes-g         ###   ########.fr       */
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
		signals_mini();
		sig_ign(SIGQUIT);
		mini.cmdline = readline("😇 Macroshell ~ ");
		if (!mini.cmdline)
		{
			if (isatty(STDIN_FILENO))
				printf("%s", "exit\n");
			break ;
		}
		if (ft_strlen(mini.cmdline))
		{
			add_history(mini.cmdline);
			lexer(&mini);
			expand(&mini);
			syntax(&mini);
			exec(&mini);
		}
	}
	return (g_sig.ret);
}
