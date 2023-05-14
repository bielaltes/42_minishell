/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/14 12:29:42 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;

int main(int argc, char **argv, char**env)
{
	t_mini mini;

	if (argc != 1 && argv[0])
		exit(1);
	init_env(&mini, env);
	mini.def_env = env;
	while (42)
	{
		//set_signals();
		mini.cmdline = readline("😇 Macroshell ~ ");
		add_history(mini.cmdline);
		lexer(&mini);
		// int i = 0;
		// for (i = 0; mini.tok_lex[i].word != NULL; ++i)x
		// 	printf("%s %d %d\n", mini.tok_lex[i].word, mini.tok_lex[i].expand, mini.tok_lex[i].type);
		syntax(&mini);
		//expand(cmd_line);
		exec(&mini);
	}
}