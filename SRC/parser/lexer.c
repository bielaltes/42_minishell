/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 08:11:54 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/11 04:59:01 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_reserved(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->tok_lex[i].word)
	{
		if (mini->tok_lex[i].type == CMD)
		{
			if (!ft_strncmp(mini->tok_lex[i].word, "env", 0xFF))
				exec_env(mini->env);
			else if (!ft_strncmp(mini->tok_lex[i].word, "cd", 0xFF))
				return ;
			else
				exit(2);
		}
		i++;
	}
}

void lexer(t_mini *mini)
{
	mini->tok_lex = ft_split_tokens(mini->cmdline, ' ');
	if (!mini->tok_lex)
		exit(2);
	assing_type(mini->tok_lex);
	check_reserved(mini);
}