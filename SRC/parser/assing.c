/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:26:59 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/26 18:04:28 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assing_input(t_token *tokens, int i)
{
	int	aux;

	aux = 2;
	tokens[i].type = REDIR_INP;
	if (tokens[i + 1].word != NULL && tokens[i + 1].word[0] != '|')
		tokens[i + 1].type = FT_FILE;
	else
		aux--;
	return (aux);
}

int	assing_output(t_token *tokens, int i)
{
	int	aux;

	aux = 2;
	tokens[i].type = REDIR_OUT;
	if (tokens[i + 1].word != NULL && tokens[i + 1].word[0] != '|')
		tokens[i + 1].type = FT_FILE;
	else
		aux--;
	return (aux);
}

int	assing_output_append(t_token *tokens, int i)
{
	int	aux;

	aux = 2;
	tokens[i].type = REDIR_APPEND;
	if (tokens[i + 1].word != NULL && tokens[i + 1].word[0] != '|')
		tokens[i + 1].type = FT_FILE;
	else
		aux--;
	return (aux);
}

int	assing_heredoc(t_token *tokens, int i)
{
	int	aux;

	aux = 2;
	tokens[i].type = REDIR_HERE;
	if (tokens[i + 1].word != NULL && tokens[i + 1].word[0] != '|')
		tokens[i + 1].type = HERE_DOC;
	else
		aux--;
	return (aux);
}

int	assing_command(t_token *tokens, int i)
{
	int	aux;

	aux = i;
	tokens[i++].type = CMD;
	while (tokens[i].word != NULL && !reserved(tokens[i].word))
	{
		tokens[i].type = ARG;
		++i;
	}
	return (i - aux);
}
