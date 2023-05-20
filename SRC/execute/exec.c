/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/19 18:42:30 by jsebasti         ###   ########.fr       */
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
        g_sig.pid = fork();
        if (g_sig.pid == 0)
        {
            redir_files(mini, i);
            if (mini->tok_lex)
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
