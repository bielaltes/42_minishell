/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/08 18:23:33 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_built(int code, char **args, t_mini *mini)
{
	if (code == 1)
		return (exec_env(mini->env));
	if (code == 2)
		return (exec_cd(mini, args));
	if (code == 3)
		return (exec_pwd(mini->env));
	if (code == 4)
		return (exec_exit(mini, args[1]));
	if (code == 5)
		return (exec_export(mini->env, args));
	if (code == 6)
		return (exec_unset(mini->env, args[1]));
	return (1);
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
	return (exec_built(code, mini->cmds[0].args, mini));
}

static void	exec_exec(t_mini *mini, int i, int p[4])
{
	int		code;
	char	**new_env;

	code = 0;
	mini->pids = malloc(sizeof(pid_t) * mini->n_cmds);
	if (mini->n_cmds == 1 && mini->tok_lex[i].word && \
			is_built_in(ft_tolower(mini->tok_lex[i].word), &code))
	{
		g_sig.ret = exec_builtin_alone(mini, p, code);
		return ;
	}
	new_env = NULL;
	while (i < mini->n_cmds)
	{
		code = 0;
		new_env = env_to_str(mini->env);
		redir_pipes(mini, p, i);
		mini->pids[i] = fork();
		if (mini->pids[i] == 0)
		{
			redir_files(mini, i, p);
			if (mini->tok_lex[i].word && \
			is_built_in(ft_tolower(mini->tok_lex[i].word), &code))
				exec_exit(mini, ft_itoa(exec_built(code, mini->cmds[i].args, \
						mini)));
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
	int		status;

	i = 0;
	p[2] = dup(0);
	p[3] = dup(1);
	exec_exec(mini, i, p);
	dup2(p[2], 0);
	dup2(p[3], 1);
	close(p[2]);
	close(p[3]);
	while (i < mini->n_cmds && waitpid(mini->pids[i], &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_sig.ret = WEXITSTATUS(status);
		++i;
	}
}
