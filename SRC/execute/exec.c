/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/14 10:26:18 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec(t_mini *mini)
{
    int p[4];
    int i;

    i = 0;
    p[2] = dup(0);
    p[3] = dup(1);
    while (i < mini->n_cmds)
    {
        redir_pipes(mini, p, i);
        mini->cmds[i].pid = fork();
        if (mini->cmds[i].pid == 0)
        {
            redir_files(mini, i);
            execve(get_path(mini->def_env, mini->cmds[i].args[0]), mini->cmds[i].args, mini->def_env);
            printf("error");
        }
        ++i;
    }
    waitpid(0, NULL, 0);
    dup2(p[2],0);
    dup2(p[1],1);
    close(p[0]);
    close(p[1]);
}
