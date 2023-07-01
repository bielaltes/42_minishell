/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:37:34 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 12:32:03 by baltes-g         ###   ########.fr       */
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

int	expandible_while(char *word, int i, int k)
{
	if (k == i)
		return (-2);
	if (word[k] == '\'')
	{
		++k;
		while (word[k] != '\0' && word[k] != '\'')
		{
			if (k == i)
				return (-1);
			++k;
		}
	}
	if (word[k] == '"')
	{
		++k;
		while (word[k] != '\0' && word[k] != '"')
		{
			if (k == i)
				return (-3);
			++k;
		}
	}
	++k;
	return (k);
}

int	expandible(char	*word, int i)
{
	int	k;

	k = 0;
	if (!word[i +1])
		return (0);
	while (word[k] != '\0')
	{
		k = expandible_while(word, i, k);
		if (k < 0)
		{
			if (k == -1)
				return (0);
			else if (k == -2)
				return (1);
			else
				return (2);
		}
	}
	return (1);
}

int	next_char(char *word, int i, char c)
{
	while (word[i] != '\0')
	{
		if (word[i] == c)
			return (i);
		++i;
	}
	return (-1);
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
