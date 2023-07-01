/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:34:02 by jsebasti          #+#    #+#             */
/*   Updated: 2023/07/01 11:19:51 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_mini(void)
{
	struct sigaction	signal;

	signal.sa_handler = &father;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(SIGINT, &signal, NULL) < 0)
		end(2, MINI, "sigaction", ESIGACTION);
}

void	signals_here(void)
{
	struct sigaction	signal;

	signal.sa_handler = &here;
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
