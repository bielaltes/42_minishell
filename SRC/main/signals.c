/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:34:02 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/08 18:39:22 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int	code)
{
	(void)code;
	if (g_sig.pid == 0)
		g_sig.exit = 1;
	else
		g_sig.exit = 130;
	g_sig.sigint = 1
}

void	set_signals(void)
{
	g_sig.sigint = 0;
	g_sig.sigout = 0;
	g_sig.exit = 0;
	g_sig.pid = 0;
}