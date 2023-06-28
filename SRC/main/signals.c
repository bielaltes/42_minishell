/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:34:02 by jsebasti          #+#    #+#             */
/*   Updated: 2023/06/28 11:44:12 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	father(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.ret = 1;
		g_sig.sigint = 1;
	}
}

void	child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		g_sig.sigint = 1;
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit\n");
		rl_on_new_line();
		g_sig.sigquit = 1;
		exit(131);
	}
}

void	signals_mini(void)
{
	struct sigaction	signal;

	signal.sa_handler = &father;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(SIGINT, &signal, NULL) < 0)
		end(2, MINI, "sigaction", ESIGACTION);
}

void	signals_child(void)
{
	struct sigaction	signal;

	signal.sa_handler = &child;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(SIGINT, &signal, 0) < 0)
		end(2, MINI, "sigaction", ESIGACTION);
	if (sigaction(SIGQUIT, &signal, 0) < 0)
		end(2, MINI, "sigaction", ESIGACTION);
}

void	sig_ign(int n)
{
	struct sigaction	signal;

	signal.sa_handler = SIG_IGN;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(n, &signal, NULL) < 0)
		end(2, MINI, "sigaction", ESIGACTION);
}
