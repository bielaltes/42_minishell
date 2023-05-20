/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:34:02 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/20 04:04:53 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int	code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("Finished with code 1.\n", STDERR);
		g_sig.exit = 1;
	}
	else
	{
		ft_putstr_fd("Finished with code 130\n", STDERR);
		g_sig.exit = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char *n_code;

	n_code = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Exit code: ", STDERR);
		ft_putstr_fd(n_code, STDERR);
		g_sig.exit = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b	\b\b", STDERR);
	free(n_code);
}

void	set_signals(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
}