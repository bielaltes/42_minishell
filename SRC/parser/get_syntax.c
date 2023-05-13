/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:22:18 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/11 18:42:20 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  n_args(t_token *token, int ini, int fi)
{
    int i;
    int sum;

    sum = 0;
    i = ini;
    while (i < fi)
    {
        if (token[i].type == CMD || token[i].type == ARG)
            ++sum;
        ++i;
    }
    return (sum);
}

void    get_args(t_mini *mini, int ini, int fi, int k)
{
    int i;

    i = 0;
    mini->cmds[k].args = malloc(1 + sizeof(char *) * n_args(mini->tok_lex, ini, fi));
    while (ini < fi)
    {
        if (mini->tok_lex[ini].type == CMD || mini->tok_lex[ini].type == ARG)
        {
            mini->cmds[k].args[i] = ft_strdup(mini->tok_lex[ini].word);
            ++i;
        }
        ++ini;
    }
    mini->cmds[k].args[i] = NULL;
}