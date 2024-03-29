/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:19:10 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/28 12:39:11 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assing_pipe(t_token *tokens, int i)
{
	tokens[i].type = PIPE;
	return (1);
}

void	assing_type(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].word != NULL && tokens[i].word[0])
	{
		if (ft_strcmp(tokens[i].word, "<") == 0)
			i += assing_input(tokens, i);
		else if (ft_strcmp(tokens[i].word, ">") == 0)
			i += assing_output(tokens, i);
		else if (ft_strcmp(tokens[i].word, ">>") == 0)
			i += assing_output_append(tokens, i);
		else if (ft_strcmp(tokens[i].word, "<<") == 0)
			i += assing_heredoc(tokens, i);
		else if (ft_strcmp(tokens[i].word, "|") == 0)
			i += assing_pipe(tokens, i);
		else
			i += assing_command(tokens, i);
	}
}

int	reserved(char *str)
{
	if (ft_strcmp(str, "<") == 0 \
		|| ft_strcmp(str, ">") == 0 \
		|| ft_strcmp(str, "<<") == 0 \
		|| ft_strcmp(str, ">>") == 0 \
		|| ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}
