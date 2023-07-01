/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:08:12 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 16:16:26 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_cmds(t_token *tokens)
{
	int	i;
	int	sum;

	i = 0;
	sum = 1;
	while (tokens[i].word != NULL)
	{
		if (tokens[i].type == PIPE)
			++sum;
		++i;
	}
	return (sum);
}

static int	syn_correct_while(t_mini *mini, int j)
{
	if (mini->tok_lex[j].type == REDIR_INP
		|| mini->tok_lex[j].type == REDIR_OUT
		|| mini->tok_lex[j].type == REDIR_APPEND
		|| mini->tok_lex[j].type == REDIR_HERE)
	{
		if (mini->tok_lex[j + 1].word == NULL
			|| (mini->tok_lex[j + 1].type != FT_FILE
				&& mini->tok_lex[j + 1].type != HERE_DOC))
		{
			g_sig.ret = 2;
			write(2, "Minishell: syntax error near unexpected token \n",
				47);
			return (0);
		}
	}
	++j;
	return (1);
}

static int	syn_correct(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	while (i < mini->n_cmds)
	{
		if (mini->cmds[i].token_ini == mini->cmds[i].token_fi)
		{
			g_sig.ret = 2;
			write(2, "Minishell: syntax error near unexpected token \n", 47);
			return (0);
		}
		j = mini->cmds[i].token_ini;
		while (j != mini->cmds[i].token_fi)
		{
			if (!syn_correct_while(mini, j))
				return (0);
			++j;
		}
		++i;
	}
	return (1);
}

int	syntax(t_mini *mini)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	mini->n_cmds = n_cmds(mini->tok_lex);
	mini->cmds = malloc(sizeof(t_simple_cmd) * mini->n_cmds);
	if (!mini->cmds)
		end(2, MINI, "malloc", MALLOCER);
	while (mini->tok_lex[i].word != NULL)
	{
		j = i;
		while (mini->tok_lex[j].word != NULL && mini->tok_lex[j].type != PIPE)
			++j;
		mini->cmds[k].token_ini = i;
		mini->cmds[k].token_fi = j;
		get_args(mini, i, j, k);
		if (mini->tok_lex[j].type == PIPE)
			++j;
		i = j;
		k++;
	}
	return (syn_correct(mini));
}
