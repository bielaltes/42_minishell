/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:17 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/13 16:13:52 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    redir_files(t_mini *mini, int i)
{
    return ;
}

void    redir_pipes(t_mini *mini, int *p, int i)
{
    if (i == mini->n_cmds-1)
    {
        dup2(p[3], 1);
        close(p[3]);
    }
    if (i != 0)
    {
        dup2(p[0], 0);
        close(p[0]);
    }
    pipe(p);
    dup2(p[1], 1);
    close(p[1]);
    
}