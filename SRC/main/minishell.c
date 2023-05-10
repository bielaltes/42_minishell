/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/09 21:07:10 by jsebasti         ###   ########.fr       */
=======
/*   Updated: 2023/05/10 15:30:43 by baltes-g         ###   ########.fr       */
>>>>>>> dc0d3a4fbdbc78c66aab701bfcbf631bc7f87b18
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;

int main(int argc, char **argv, char **env)
{
	t_mini mini;

	if (argc != 1)
		exit(1);
	init_env(&mini, env);
	while (42)
	{
		//set_signals();
		mini.cmdline = readline("😇 Macroshell >");
		add_history(mini.cmdline);
		lexer(&mini);
		int i = 0;
		for (i = 0; mini.tok_lex[i].word != NULL; ++i)
			printf("%s %d %d\n", mini.tok_lex[i].word, mini.tok_lex[i].expand, mini.tok_lex[i].type);
		//syntax(cmd_line);
		//expand(cmd_line);
		//execute(cmd_line);
	}
}