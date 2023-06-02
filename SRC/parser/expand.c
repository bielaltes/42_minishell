/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:58:05 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/02 15:39:35 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	divide_token(t_token *tok)
{
	char	*word;
	int		i;

	i = 0;
	word = tok->word;
	if (word[i + word_len(word)] == '\0')
	{
		tok->expand = 0;
		return ;
	}
	else
		tok->expand = 1;
	tok->sub_tok = malloc(sizeof(t_token) * count_subs(word));
}*/

static int	next_dollar(char *word, int i)
{
	while (word[i] != '\0')
	{
		if (word[i] == '$')
			return (i);
		++i;
	}
	return (-1);
}

void	expand_token(t_mini *mini, t_token *tok)
{
	char	*word;
	char	*aux;
	char	*aux2;
	int		i;
	int		k;

	word = tok->word;
	if (next_dollar(word, 0) == -1)
		return ;
	i = next_dollar(word, 0);
	aux = ft_substr(word, 0, i);
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			k = i;
			while (word[i + k] != '\0' && word[i + k] != '\'' && word[i + k] != '"')
				++k;
			//aux2 = search_env(mini->env, ft_substr(word, i+1, k), 1);
			aux2 = "soc una prova";
			aux = ft_strjoin(aux, aux2);
			i += k;
			if (word[i] != '\0')
				i++;
		}
		else
		{
			k = next_dollar(word, i);
			if (k == -1)
			{
				k = 0;
				while (word[k] != '\0')
					++k;
			}
			aux = ft_strjoin(aux, ft_substr(aux, i, k -1));
		}
	}
	free(word);
	tok->word = aux;
}

void	expand(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->tok_lex[i].word != NULL)
	{
		expand_token(mini, &mini->tok_lex[i]);
		//divide_token(mini->tok_lex[i]);
		//*leave_quotes(t_mini->tok_lex[i]);*/
		++i;
	}
}
