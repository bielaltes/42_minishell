/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:26:59 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/10 15:46:26 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int assing_input(t_token *tokens, int i)
{
    tokens[i].type = REDIR_INP;
    if (tokens[i+1].word != NULL)
        tokens[i+1].type = FT_FILE;
    else
        exit(2);
    return (2);
}

int assing_output(t_token *tokens, int i)
{
    tokens[i].type = REDIR_OUT;
    if (tokens[i+1].word != NULL)
        tokens[i+1].type = FT_FILE;
    else
        exit(2);
    return (2);
}

int assing_output_append(t_token *tokens, int i)
{
    tokens[i].type = REDIR_APPEND;
    if (tokens[i+1].word != NULL)
        tokens[i+1].type = FT_FILE;
    else
        exit(2);
    return (2);
}

int assing_heredoc(t_token *tokens, int i)
{
    tokens[i].type = REDIR_HERE;
    if (tokens[i+1].word != NULL)
        tokens[i+1].type = HERE_DOC;
    else
        exit(2);
    return (2);
}

int assing_command(t_token *tokens, int i)
{
    tokens[i++].type = CMD;
    while (tokens[i].word != NULL && !reserved(tokens[i].word))
    {
        tokens[i].type = ARG;
        ++i;
    }
    return (i);
}