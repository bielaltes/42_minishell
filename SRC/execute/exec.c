/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:01:03 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 15:52:42 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_while_if(t_mini *mini, int i, int p[4], int code)
{
	char	**new_env;
	char	**aux;

	new_env = env_to_str(mini->env);
	signals_child();
	if (redir_files(mini, i) == FAILURE)
		exit(1);
	if (mini->tok_lex[i].word && \
			is_built_in(ft_tolower(mini->tok_lex[i].word), &code))
	{
		aux = ft_split(ft_strjoin(ft_itoa(exec_built(code,
							mini->cmds[i].args, mini)),
					"|", FIRST), '|');
		exec_exit(mini, aux);
	}
	else
	{
		if (mini->n_cmds != 1)
			close(p[0]);
		execve(get_path(new_env, mini->cmds[i].args[0], new_env), \
		mini->cmds[i].args, new_env);
		end(126, MINI, get_path(new_env, mini->cmds[i].args[0],
				new_env), ISDIR);
	}
	free(new_env);
}

static void	exec_while(t_mini *mini, int p[4], int i, int code)
{
	redir_pipes(mini, p, i);
	mini->pids[i] = fork();
	if (mini->pids[i] < 0)
		end(2, MINI, "fork", EFORK);
	if (mini->pids[i] == 0)
	{
		exec_while_if(mini, i, p, code);
	}
	close_heres(mini, i);
}

static void	exec_exec(t_mini *mini, int i, int p[4])
{
	int		code;

	code = 0;
	mini->pids = malloc(sizeof(pid_t) * mini->n_cmds);
	if (!mini->pids)
		end(2, MINI, "malloc", MALLOCER);
	if (do_heres(mini) == FAILURE)
		return ;
	if (mini->n_cmds == 1 && mini->tok_lex[i].word && \
			is_built_in(ft_tolower(mini->tok_lex[i].word), &code))
	{
		g_sig.ret = exec_builtin_alone(mini, code);
		return ;
	}
	sig_ign(SIGINT);
	while (i < mini->n_cmds)
	{
		exec_while(mini, p, i, code);
		++i;
	}
}

static int	handle_exit(int exit_status, int flag)
{
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
	{
		if (WCOREDUMP(exit_status))
			end(SUCCESS, MINI, ": core dumped in child", NULL);
		if (WTERMSIG(exit_status) == SIGINT)
		{
			if (flag)
				ft_printf("\n");
			return (130);
		}
		if (WTERMSIG(exit_status) == SIGQUIT)
		{
			if (flag)
				ft_printf("Quit: 3\n");
			return (131);
		}
	}
	return (1);
}

void	exec(t_mini *mini)
{
	int		p[4];
	int		i;
	int		status;

	i = 0;
	p[2] = dup(0);
	p[3] = dup(1);
	if (p[2] < 0 || p[3] < 0)
		end(2, MINI, "dup", DUPERR);
	exec_exec(mini, i, p);
	if (dup2(p[2], 0) < 0 || dup2(p[3], 1) < 0)
		end(2, MINI, "dup2", DUPERR);
	if (close(p[2]) < 0 || close(p[3]) < 0)
		end(2, MINI, "close", CCLOSE);
	while (i < mini->n_cmds && waitpid(mini->pids[i], &status, 0) > 0)
	{
		if (i == mini->n_cmds -1)
			g_sig.ret = handle_exit(status, 1);
		else
			g_sig.ret = handle_exit(status, 0);
		++i;
	}
	free(mini->pids);
}
