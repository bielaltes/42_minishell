/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:58:05 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 12:22:16 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_token_while_if(char *word, int i, char **aux)
{
	int	k;

	k = next_char(word, i + 1, '$');
	if (k == -1)
	{
		k = i;
		while (word[k] != '\0')
			++k;
	}
	*aux = ft_strjoin(*aux, ft_substr(word, i, k - i, NO), NO);
	if (!*aux)
		end(2, MINI, "malloc", MALLOCER);
	return (k);
}

static int	expand_token_while(t_mini *mini, char *word, int i, char **aux)
{
	int		k;
	char	*aux2;

	if (word[i] == '$' && expandible(word, i))
	{
		k = ++i;
		while (word[k] != '\0' && word[k] != '\'' && word[k] != '"'
			&& word[k] != '$' && !is_spacer(word[k]))
			++k;
		aux2 = search_env(mini->env, ft_substr(word, i, k - i, NO));
		if (aux2)
			*aux = ft_strjoin(*aux, aux2, NO);
		if (!ft_strcmp(ft_substr(word, i, k - i, NO), "?"))
			*aux = ft_strjoin(*aux, ft_itoa(g_sig.ret), NO);
		else if (!aux2 && word[k] == '\'' && k >= 2 && word[k -2] == '\'')
			*aux = ft_strjoin(*aux, "$", NO);
		if (!*aux)
			end(2, MINI, "malloc", MALLOCER);
		i = k;
		free(aux2);
	}
	else
		i = expand_token_while_if(word, i, aux);
	return (i);
}

void	expand_token(t_mini *mini, t_token *tok)
{
	char	*word;
	char	*aux;
	int		i;

	word = tok->word;
	if (next_char(word, 0, '$') == -1)
		return ;
	i = next_char(word, 0, '$');
	aux = ft_substr(word, 0, i, NO);
	if (!aux)
		end(2, MINI, "malloc", MALLOCER);
	while (word[i] != '\0')
	{
		i = expand_token_while(mini, word, i, &aux);
	}
	free(word);
	if (aux != NULL)
		tok->word = aux;
	else
		tok->word = ft_strdup("", NO);
	if (!tok->word)
		end(2, MINI, "malloc", MALLOCER);
}

void	expand(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->tok_lex[i].word != NULL)
	{
		expand_token(mini, &mini->tok_lex[i]);
		leave_quotes(&mini->tok_lex[i]);
		++i;
	}
}
