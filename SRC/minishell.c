/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/07 21:06:30 by baltes-g         ###   ########.fr       */
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

int main2(int argc, char **argv, char **env)
{
	t_cmdline cmdline;

	if (argc != 1)
		exit(1);
	init_env(&cmdline, env);
	while (42)
	{
		set_signals();
		cmdline.read = readline("macroshell>");
		add_history(cmdline.read);
		lexer(cmd_line);
		syntax(cmd_line);
		expand(cmd_line);
		execute(cmd_line);
	}
}