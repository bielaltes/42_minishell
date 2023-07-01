/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:21:38 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 12:22:12 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	leave_quotes_while(char *word, char **aux, int i)
{
	int		k;
	char	lim;

	while (i != -1 && word[i] != '\0')
	{
		lim = word[i++];
		k = i;
		while (word[k] != lim)
			++k;
		*aux = ft_strjoin(*aux, ft_substr(word, i, k - i, NO), BOTH);
		i = next_quote(word, ++k);
		if (i != -1)
			*aux = ft_strjoin(*aux, ft_substr(word, k, i - k, NO), BOTH);
		if (!*aux)
			end(2, MINI, "malloc", MALLOCER);
	}
	return (k);
}

void	leave_quotes(t_token *tok)
{
	char	*aux;
	char	*word;
	int		k;
	int		i;

	i = 0;
	word = tok->word;
	i = next_quote(word, 0);
	if (i == -1)
		return ;
	aux = ft_substr(word, 0, i, NO);
	if (!aux)
		end(2, MINI, "malloc", MALLOCER);
	k = leave_quotes_while(word, &aux, i);
	if (word[k] != '\0')
		aux = ft_strjoin(aux, &word[k], FIRST);
	if (!aux)
		end(2, MINI, "malloc", MALLOCER);
	free(word);
	tok->word = aux;
}
