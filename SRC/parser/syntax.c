/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:08:12 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/03 18:28:24 by baltes-g         ###   ########.fr       */
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

void	syntax(t_mini *mini)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	mini->n_cmds = n_cmds(mini->tok_lex);
	mini->cmds = malloc(sizeof(t_simple_cmd) * mini->n_cmds);
	if (!mini->cmds)
		return ;
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
}
