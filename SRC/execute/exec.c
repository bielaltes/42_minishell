/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/17 19:35:57 by baltes-g         ###   ########.fr       */
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
            execve(get_path(mini->def_env, mini->cmds[i].args[0]), \
			mini->cmds[i].args, mini->def_env);
            printf("error");
        }
        ++i;
    }
	dup2(p[2],0);
    dup2(p[3],1);
    close(p[2]);
    close(p[3]);
	while (waitpid(-1, NULL, 0) != -1);
}