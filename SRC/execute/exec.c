/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/20 04:00:41 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_built_in(char *cmd, t_mini *mini)
{
	if (!ft_strncmp(cmd, "env", 0xFF))
		return (exec_env(mini->env));
	else if (!ft_strncmp(cmd, "cd", 0xFF))
		return (exec_cd(mini));
	else if (!ft_strncmp(cmd, "pwd", 0xFF))
		return (exec_pwd(mini->env));
	else if (!ft_strncmp(cmd, "exit", 0xFF))
		return (exec_exit(mini));
	return (1);
}

void	exec(t_mini *mini)
{
	int	p[4];
	int	i;

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
			if (!is_built_in(ft_tolower(mini->tok_lex[i].word), mini))
			{	
				i++;
				printf("error");
			}
			else
				execve(get_path(mini->def_env, mini->cmds[i].args[0]), \
				mini->cmds[i].args, mini->def_env);
		}
		++i;
	}
	dup2(p[2],0);
	dup2(p[3],1);
	close(p[2]);
	close(p[3]);
	while (waitpid(-1, NULL, 0) != -1);
}
