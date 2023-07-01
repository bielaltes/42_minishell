/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:26:40 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 16:10:46 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end(int status, char *str1, char *str2, char *str3)
{
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	exit(status);
}

void static	free_unset(t_env *env, char *s)
{
	t_node_env	*aux;

	if (env->size == 0)
		return ;
	env->size -= 1;
	aux = env->first;
	while (ft_strcmp(aux->data, s) && aux->next)
		aux = (aux->next);
	if (aux->prev && env->size != 0)
		aux->prev->next = aux->next;
	if (aux->next && env->size != 0)
		aux->next->prev = aux->prev;
	if (env->last == aux)
		env->last = aux->prev;
	if (env->first == aux)
		env->first = aux->next;
	free(aux->data);
	free(aux->value);
	free(aux);
}

void	free_env(t_env *env)
{
	while (env->size != 0)
		free_unset(env, env->first->data);
	free(env);
}

void	free_split(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		free(argv[i++]);
}

void	free_cmd(t_mini *mini)
{
	int				i;
	t_token			*tok;
	t_simple_cmd	*cmds;

	i = 0;
	tok = mini->tok_lex;
	cmds = mini->cmds;
	while (tok[i].word != NULL)
		free(tok[i++].word);
	free(tok);
	i = 0;
	while (i < mini->n_cmds && cmds[i].args)
	{
		free_split(cmds[i].args);
		free(cmds[i].args);
		++i;
	}
	free(mini->cmds);
}
