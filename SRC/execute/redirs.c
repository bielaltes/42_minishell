/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:17 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/27 16:18:18 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_inp(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Macroshell: ", 12);
		perror(file);
		return (FAILURE);
	}
	dup2(fd, 0);
	return (SUCCESS);
}

static int	redir_out(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		write(2, "Macroshell: ", 12);
		perror(file);
		return (FAILURE);
	}
	dup2(fd, 1);
	return (SUCCESS);
}

static int redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		write(2, "Macroshell: ", 12);
		perror(file);
		return (FAILURE);
	}
	dup2(fd, 1);
	return (SUCCESS);
}

static int	redir_here(char *file, int p[4])
{
	int		fd[2];
	char	*line;

	dup2(p[2], 0);
	pipe(fd);
	line = readline("heredoc>");
	while (line && ft_strncmp(line, file, 0xFF))
	{
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		line = readline("heredoc>");
	}
	close(fd[1]);
	dup2(fd[0], 0);
	return (SUCCESS);
}

int	redir_files(t_mini *mini, int j, int p[4])
{
	int	i;
	int	exit;

	exit = SUCCESS;
	i = mini->cmds[j].token_ini;
	while (i != mini->cmds[j].token_fi && exit == SUCCESS)
	{
		if (mini->tok_lex[i].type == REDIR_INP)
		{
			if (mini->tok_lex[i + 1].type == FT_FILE)
				exit = redir_inp(mini->tok_lex[i + 1].word);
		}
		else if (mini->tok_lex[i].type == REDIR_OUT)
		{
			if (mini->tok_lex[i + 1].type == FT_FILE)
				exit = redir_out(mini->tok_lex[i + 1].word);
		}
		if (mini->tok_lex[i].type == REDIR_HERE)
			if (mini->tok_lex[i + 1].type == HERE_DOC)
				exit = redir_here(mini->tok_lex[i + 1].word, p);
		if (mini->tok_lex[i].type == REDIR_APPEND)
			if (mini->tok_lex[i + 1].type == FT_FILE)
				exit = redir_append(mini->tok_lex[i + 1].word);
		++i;
	}
	return (exit);
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
