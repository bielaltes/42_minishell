/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/14 10:14:27 by jsebasti         ###   ########.fr       */
=======
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/14 09:58:53 by baltes-g         ###   ########.fr       */
>>>>>>> d059a1dd8d48e8fa51c56fca3f394b4766b7a0a7
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
// void    exec(t_mini *mini)
// {
//     int p[2];
//     int i;

//     i = 0;
//     while (mini->cmds[i])
//     {
//         if (mini->cmds[i + 1])
//             pipe(p);
//         mini->cmds[i].pid = fork();

//         redir();
//         do_execve();
//         ++i;
//     }    
// }
=======
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
>>>>>>> d059a1dd8d48e8fa51c56fca3f394b4766b7a0a7
