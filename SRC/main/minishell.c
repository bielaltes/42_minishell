/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/07 15:17:56 by jsebasti         ###   ########.fr       */
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
				write(2, "\nexit\n", 6);
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
	return (0);
}
