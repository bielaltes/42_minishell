/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 08:11:54 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/16 20:58:13 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lexer(t_mini *mini)
{
	mini->tok_lex = ft_split_tokens(mini->cmdline, ' ');
	if (!mini->tok_lex)
		exit(2);
	assing_type(mini->tok_lex);
}