/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:18:15 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 11:19:52 by baltes-g         ###   ########.fr       */
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
		ft_printf("\n");
		rl_on_new_line();
		g_sig.sigint = 1;
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("Quit\n");
		rl_on_new_line();
		g_sig.sigquit = 1;
		exit(131);
	}
}

void	here(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		g_sig.ret = 1;
		g_sig.sigint = 1;
	}
}
