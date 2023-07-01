/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:29:36 by jsebasti          #+#    #+#             */
/*   Updated: 2023/07/01 16:22:35 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig;

static void	minishell(t_mini *mini)
{
	signals_mini();
	sig_ign(SIGQUIT);
	mini->cmdline = readline("Macroshell ~ ");
	if (!mini->cmdline)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		g_sig.exit = 1;
		return ;
	}
	if (ft_strlen_mini(mini->cmdline))
	{
		add_history(mini->cmdline);
		if (!misuse(mini->cmdline))
		{
			lexer(mini);
			expand(mini);
			if (syntax(mini))
				exec(mini);
			free_cmd(mini);
		}
	}
	free(mini->cmdline);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1 && argv[0])
		exit(1);
	init_env(&mini, env);
	g_sig.exit = 0;
	while (g_sig.exit == 0)
		minishell(&mini);
	free_env(mini.env);
	return (g_sig.ret);
}
