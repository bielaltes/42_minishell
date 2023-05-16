/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 08:11:54 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/16 01:30:41 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_reserved(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->tok_lex[i].word)
	{
		if (mini->tok_lex[i].type == CMD)
		{
			if (!ft_strncmp(mini->tok_lex[i].word, "env", 0xFF))
				return (exec_env(mini->env));
			else if (!ft_strncmp(mini->tok_lex[i].word, "cd", 0xFF))
				return (0);
			else if (!ft_strncmp(mini->tok_lex[i].word, "echo", 0xFF))
				return 0;
			else if (!ft_strncmp(mini->tok_lex[i].word, "exit", 0xFF))
				return 0;
			else if (!ft_strncmp(mini->tok_lex[i].word, "pwd", 0xFF))
				return (exec_pwd(mini->env));
			else if (!ft_strncmp(mini->tok_lex[i].word, "unset", 0xFF))
				return 0;
			else
				return 0;
		}
		i++;
	}
    return (1);
}

void lexer(t_mini *mini)
{
	mini->tok_lex = ft_split_tokens(mini->cmdline, ' ');
	if (!mini->tok_lex)
		exit(2);
	assing_type(mini->tok_lex);
	check_reserved(mini);

}