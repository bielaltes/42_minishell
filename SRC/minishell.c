/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/08 09:44:36 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_signal(void)
// {
// 	signal();
// }

/*int	main(int ac, char **av, char **env)
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
}*/

int main(int argc, char **argv, char **env)
{
	t_mini mini;

	if (argc != 1)
		exit(1);
	init_env(&mini, env);
	while (42)
	{
		//set_signals();
		mini.cmdline = readline("macroshell>");
		add_history(mini.cmdline);
		lexer(&mini);
		int i = 0;
		for (i = 0; mini.tok_lex[i].word != NULL; ++i)
			printf("%s %d\n", mini.tok_lex[i].word, mini.tok_lex[i].expand);
		//syntax(cmd_line);
		//expand(cmd_line);
		//execute(cmd_line);
	}
}