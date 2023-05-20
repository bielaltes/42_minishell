/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/21 01:25:59 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_built(int code, char **args, t_mini *mini)
{
	if (code == 1)
		exec_env(mini->env);
	if (code == 2)
		exec_cd(mini, args);
	if (code == 3)
		exec_pwd(mini->env);
	if (code == 4)
		exec_exit(mini, args[1]);
	if (code == 5)
		exec_export(mini, args[1]);
}

static int	is_built_in(char *cmd, int *code)
{
	if (!ft_strncmp(cmd, "env", 0xFF))
		*code = 1;
	else if (!ft_strncmp(cmd, "cd", 0xFF))
		*code = 2;
	else if (!ft_strncmp(cmd, "pwd", 0xFF))
		*code = 3;
	else if (!ft_strncmp(cmd, "exit", 0xFF))
		*code = 4;
	else if (!ft_strncmp(cmd, "export", 0xFF))
		*code = 5;
	return (*code);
}

void	exec(t_mini *mini)
{
	int	p[4];
	int	i;
	int code;

	i = 0;
	p[2] = dup(0);
	p[3] = dup(1);
	while (i < mini->n_cmds)
	{
		code = 0;
		redir_pipes(mini, p, i);
		if (is_built_in(ft_tolower(mini->tok_lex[i].word), &code))
		{
			exec_built(code, mini->cmds[i].args, mini);
			i++;
		}
		else
		{
			g_sig.pid = fork();
			if (g_sig.pid == 0)
			{
				redir_files(mini, i);
				execve(get_path(mini->def_env, mini->cmds[i].args[0]), \
				mini->cmds[i].args, mini->def_env);
			}
			++i;
		}
	}
	dup2(p[2],0);
	dup2(p[3],1);
	close(p[2]);
	close(p[3]);
	while (waitpid(-1, NULL, 0) != -1);
}
