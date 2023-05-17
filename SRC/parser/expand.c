/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:58:05 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/17 20:27:41 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	should_expand(t_token *tok)
{
	int	i;

	i = 0;
	while (tok->word[i] && tok->word[i] != '\0')
	{
		if (tok->word[i] == '$' && /*tok->expand[i]*/)
			return (1);
		++i;
	}
	return (0);
}

static void	expand_token(t_token *tok)
{
	char	*env_var;
	char	**splited_env;

	if (should_expand(tok))
	{

	}
}

void expand(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->tok_lex[i].word != NULL)
	{
		if (mini->tok_lex[i].type == EXPAND)
			expand_token(mini->tok_lex[i]);
		++i;
	}

}