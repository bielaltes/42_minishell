/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:58:05 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/18 17:19:20 by jsebasti         ###   ########.fr       */
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

int	expandible(char	*word, int i)
{
	int	k;

	k = 0;
	while (word[k] != '\0')
	{
		if (k == i)
			return (1);
		if (word[k] == '\'')
		{
			++k;
			while (word[k] != '\0' && word[k] != '\'')
			{
				if (k == i)
					return (0);
				++k;
			}
		}
		if (word[k] == '"')
		{
			++k;
			while (word[k] != '\0' && word[k] != '"')
			{
				if (k == i)
					return (1);
				++k;
			}
		}
		++k;
	}
	return (1);
}

static int	next_char(char *word, int i, char c)
{
	while (word[i] != '\0')
	{
		if (word[i] == c)
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
	if (next_char(word, 0, '$') == -1)
		return ;
	i = next_char(word, 0, '$');
	aux = ft_substr(word, 0, i);
	while (word[i] != '\0')
	{
		//printf("expandible: %c %d\n", word[i], expandible(word, i));
		if (word[i] == '$' && expandible(word, i) && word[i+1])
		{
			k = i;
			while (word[k] != '\0' && word[k] != '\'' && word[k] != '"')
				++k;
			aux2 = search_env(mini->env, ft_substr(word, i + 1, k - i -1));
			if (aux2)
				aux = ft_strjoin(aux, aux2);
			if (!ft_strcmp(ft_substr(word, i + 1, k - i -1), "?"))
				aux = ft_strjoin(aux, ft_itoa(g_sig.ret));
			i = k;
		}
		else
		{
			k = next_char(word, i + 1, '$');
			if (k == -1)
			{
				k = i;
				while (word[k] != '\0')
					++k;
			}
			aux = ft_strjoin(aux, ft_substr(word, i, k - i));
			i = k;
		}
	}
	free(word);
	tok->word = aux;
}

int	next_quote(char *word, int i)
{
	int	a;
	int	b;

	a = next_char(word, i, '\'');
	b = next_char(word, i, '"');
	if (a == -1 && b == -1)
		return (-1);
	else if (a == -1)
		return (b);
	else if (b == -1)
		return (a);
	else if (a > b)
		return (b);
	else if (b > a)
		return (a);
	else
		return (-1);
}

void	leave_quotes(t_token *tok)
{
	char	*aux;
	char	*word;
	int		k;
	char	lim;
	int		i;

	i = 0;
	word = tok->word;
	i = next_quote(word, 0);
	if (i == -1)
		return ;
	aux = ft_substr(word, 0, i);
	while (i != -1 && word[i] != '\0')
	{
		lim = word[i++];
		k = i;
		while (word[k] != lim)
			++k;
		aux = ft_strjoin(aux, ft_substr(word, i, k - i));
		i = next_quote(word, ++k);
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
		/*divide_token(mini->tok_lex[i]);*/
		leave_quotes(&mini->tok_lex[i]);
		++i;
	}
}
