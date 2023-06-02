/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:19:10 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/02 01:39:52 by jsebasti         ###   ########.fr       */
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
		if (ft_strncmp(tokens[i].word, "<", 0xFF) == 0)
			i += assing_input(tokens, i);
		else if (ft_strncmp(tokens[i].word, ">", 0xFF) == 0)
			i += assing_output(tokens, i);
		else if (ft_strncmp(tokens[i].word, ">>", 0xFF) == 0)
			i += assing_output_append(tokens, i);
		else if (ft_strncmp(tokens[i].word, "<<", 0xFF) == 0)
			i += assing_heredoc(tokens, i);
		else if (ft_strncmp(tokens[i].word, "|", 0xFF) == 0)
			i += assing_pipe(tokens, i);
		else
			i += assing_command(tokens, i);
	}
}

int	reserved(char *str)
{
	if (ft_strncmp(str, "<", 0xFF) == 0 \
		|| ft_strncmp(str, ">", 0xFF) == 0 \
		|| ft_strncmp(str, "<<", 0xFF) == 0 \
		|| ft_strncmp(str, ">>", 0xFF) == 0 \
		|| ft_strncmp(str, "|", 0xFF) == 0)
		return (1);
	return (0);
}
