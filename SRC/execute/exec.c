/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/11 20:14:55 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec(t_mini *mini)
{
    int p[2];
    int i;

    i = 0;
    while (mini->cmds[i])
    {
        if (mini->cmds[i + 1])
            pipe(p);
        mini->cmds[i].pid = fork();

        redir();
        do_execve();
        ++i;
    }    
}