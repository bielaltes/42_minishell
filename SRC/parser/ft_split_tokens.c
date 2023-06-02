/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:50:10 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/02 15:10:18 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_spacer(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else if (c == '|' || c == '<' || c == '>')
		return (2);
	return (0);
}

static int	word_len(char *str, int i, char c)
{
	int	util;
	int	len;

	len = 0;
	util = is_spacer(str[i]);
	while (str[i] && is_spacer(str[i]) == util)
	{
		++len;
		++i;
		if (str[i -1] == '\'')
		{
			while (str[i++] != '\'')
				++len;
			++len;
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
				++len;
			++len;
		}
	}
	return (len);
}

static int	count_words(char *s, char c)
{
	int	sum;
	int	aux;
	int	i;

	i = 0;
	sum = 0;
	while (s[i] != '\0')
	{
		while (is_spacer(s[i]) == 1)
			++i;
		if (s[i] == '\0')
			break ;
		aux = word_len(s, i, c);
		i += aux;
		sum++;
	}
	return (sum);
}

static t_token	*malloc_error(t_token *new, int j)
{
	while (j >= 0)
	{
		free(new[j].word);
		--j;
	}
	free(new);
	return (NULL);
}

t_token	*ft_split_tokens(char *s, char c)
{
	int		i;
	int		j;
	t_token	*new;

	new = malloc(sizeof(t_token) * (count_words(s, c) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < count_words(s, c))
	{
		while (is_spacer(s[i]) == 1)
			++i;
		new[j].word = ft_substr(s, i, word_len(&s[i], 0, c));
		if (!new[j].word)
			return (malloc_error(new, j));
		ft_check_escaped(new[j].word);
		i += word_len(&s[i], 0, c);
		ft_printf("word: %s|\n", new[j].word);
	}
	new[j].word = (NULL);
	return (new);
}
