/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/07 13:37:56 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_built(int code, char **args, t_mini *mini)
{
	if (code == 1)
		if (exec_env(mini->env))
			return (1);
	if (code == 2)
		if (exec_cd(mini, args))
			return (1);
	if (code == 3)
		if (exec_pwd(mini->env))
			return (1);
	if (code == 4)
		if (exec_exit(mini, args[1]))
			return (1);
	if (code == 5)
		if (exec_export(mini->env, args[1]))
			return (1);
	if (code == 6)
		if (exec_unset(mini->env, args[1]))
			return (1);
	return (0);
}

static int	is_built_in(char *cmd, int *code)
{
	if (!ft_strcmp(cmd, "env"))
		*code = 1;
	else if (!ft_strcmp(cmd, "cd"))
		*code = 2;
	else if (!ft_strcmp(cmd, "pwd"))
		*code = 3;
	else if (!ft_strcmp(cmd, "exit"))
		*code = 4;
	else if (!ft_strcmp(cmd, "export"))
		*code = 5;
	else if (!ft_strcmp(cmd, "unset"))
		*code = 6;
	return (*code);
}

static int	exec_builtin_alone(t_mini *mini, int p[4], int code)
{
	redir_pipes(mini, p, 0);
	if (exec_built(code, mini->cmds[0].args, mini))
		return (1);
	return (1);
}

static void	exec_exec(t_mini *mini, int i, int p[4])
{
	int		code;
	char	**new_env;

	code = 0;
	if (mini->n_cmds == 1 && mini->tok_lex[i].word && \
			is_built_in(ft_tolower(mini->tok_lex[i].word), &code))
		if (exec_builtin_alone(mini, p, code))
			return ;
	new_env = NULL;
	while (i < mini->n_cmds)
	{
		code = 0;
		new_env = env_to_str(mini->env);
		redir_pipes(mini, p, i);
		g_sig.pid = fork();
		if (g_sig.pid == 0)
		{
			redir_files(mini, i, p);
			if (mini->tok_lex[i].word && \
				is_built_in(ft_tolower(mini->tok_lex[i].word), &code))
			{
				exec_built(code, mini->cmds[i].args, mini);
				exec_exit(mini, "1");
			}
			else
			{
				if (i != 0)
					close(p[0]);
				execve(get_path(new_env, mini->cmds[i].args[0]), \
				mini->cmds[i].args, new_env);
			}
		}
		++i;
		free(new_env);
	}
}

void	exec(t_mini *mini)
{
	int		p[4];
	int		i;

	i = 0;
	p[2] = dup(0);
	p[3] = dup(1);
	exec_exec(mini, i, p);
	dup2(p[2], 0);
	dup2(p[3], 1);
	close(p[2]);
	close(p[3]);
	while (waitpid(-1, NULL, 0) != -1)
		;
}
