/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:17 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/19 02:59:54 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_inp(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		end(1, MINI, file, EROPEN);
	dup2(fd, 0);
}

static void	redir_out(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		end(1, MINI, file, ERCREAT);
	dup2(fd, 1);
}

static void	redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		end(1, MINI, file, ERCREAT);
	dup2(fd, 1);
}

static void	redir_here(char *file, int p[4])
{
	int		fd[2];
	// int		p_aux;
	char	*line;

	// p_aux = dup(0);
	dup2(p[2], 0);
	pipe(fd);
	line = readline("heredoc>");
	while (ft_strncmp(line, file, 0xFF))
	{
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		line = readline("heredoc>");
	}
	close(fd[1]);
	dup2(fd[0], 0);
}

void	redir_files(t_mini *mini, int j, int p[4])
{
	int	i;

	i = mini->cmds[j].token_ini;
	while (i != mini->cmds[j].token_fi)
	{
		if (mini->tok_lex[i].type == REDIR_INP)
		{
			if (mini->tok_lex[i + 1].type == FT_FILE)
				redir_inp(mini->tok_lex[i + 1].word);
		}
		else if (mini->tok_lex[i].type == REDIR_OUT)
		{
			if (mini->tok_lex[i + 1].type == FT_FILE)
				redir_out(mini->tok_lex[i + 1].word);
		}
		if (mini->tok_lex[i].type == REDIR_HERE)
			if (mini->tok_lex[i + 1].type == HERE_DOC)
				redir_here(mini->tok_lex[i + 1].word, p);
		if (mini->tok_lex[i].type == REDIR_APPEND)
			if (mini->tok_lex[i + 1].type == FT_FILE)
				redir_append(mini->tok_lex[i + 1].word);
		++i;
	}
}

void	redir_pipes(t_mini *mini, int *p, int i)
{
	if (i != 0)
	{
		dup2(p[0], 0);
		close(p[0]);
	}
	if (i == mini->n_cmds - 1)
	{
		dup2(p[3], 1);
		close(p[3]);
		return ;
	}
	pipe(p);
	dup2(p[1], 1);
	close(p[1]);
}
