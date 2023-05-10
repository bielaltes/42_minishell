/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:19:10 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/10 15:16:41 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    assing_type(t_token *tokens)
{
    int i;

    i = 0;
    while (tokens[i].word != NULL)
    {
        while (tokens[i].word != NULL && ft_strncmp(tokens[i].word, "\n", 0xFF) != 0)
        {
            if (ft_strncmp(tokens[i].word, "<", 0xFF) == 0)
                i += assing_input(tokens, i);
            else if (ft_strncmp(tokens[i].word, ">", 0xFF) == 0)
                i += assing_output(tokens, i);
            else if (ft_strncmp(tokens[i].word, ">>", 0xFF) == 0)
                i += assing_output_append(tokens, i);
            else if (ft_strncmp(tokens[i].word, "<<", 0xFF) == 0)
                i += assing_heredoc(tokens, i);
            else
                i += assing_cmd(tokens, i);
        }
        if (tokens[i].word != NULL)
            tokens[i++].type = PIPE;
    }
}

int reserved(char *str)
{
    if (ft_strncmp(tokens[i].word, "<", 0xFF) == 0 ||
            ft_strncmp(tokens[i].word, ">", 0xFF) == 0 ||
            ft_strncmp(tokens[i].word, "<<", 0xFF) == 0 ||
            ft_strncmp(tokens[i].word, ">>", 0xFF) == 0 ||
            ft_strncmp(tokens[i].word, "|", 0xFF) == 0)
        return (1);
    return (0);
}