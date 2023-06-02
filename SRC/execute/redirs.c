/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:17 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/17 19:51:13 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    redir_files(t_mini *mini, int i)
{
    if (i)
        i = mini->n_cmds;
    return ;
}

void    redir_pipes(t_mini *mini, int *p, int i)
{
    if (i != 0)
    {
        dup2(p[0], 0);
        close(p[0]);
    }
    if (i == mini->n_cmds-1)
    {
        dup2(p[3], 1);
        close(p[3]);
        return ;
    }
    pipe(p);
    dup2(p[1], 1);
    close(p[1]);
    
}