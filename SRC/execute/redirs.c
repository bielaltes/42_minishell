/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:17 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/29 18:01:00 by baltes-g         ###   ########.fr       */
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

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP
			| S_IROTH);
	if (fd < 0)
	{
		write(2, "Macroshell: ", 12);
		perror(file);
		return (FAILURE);
	}
	dup2(fd, 1);
	return (SUCCESS);
}

static int	redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		write(2, "Macroshell: ", 12);
		perror(file);
		return (FAILURE);
	}
	dup2(fd, 1);
	return (SUCCESS);
}

static int	redir_here(int fd)
{
	if (dup2(fd, 0) < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	redir_files(t_mini *mini, int j)
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
				exit = redir_here(mini->tok_lex[i + 1].fd_here);
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
		if (dup2(p[0], 0) < 0)
			end(2, MINI, "dup2", DUPERR);
		if (close(p[0]) < 0)
			end(2, MINI, "close", CCLOSE);
	}
	if (i == mini->n_cmds - 1)
	{
		if (dup2(p[3], 1) < 0)
			end(2, MINI, "dup2", DUPERR);
		return ;
	}
	if (pipe(p) < 0)
		end(2, MINI, "pipe", ERPIPE);
	if (dup2(p[1], 1) < 0)
		end(2, MINI, "dup2", DUPERR);
	if (close(p[1]) < 0)
		end(2, MINI, "close", CCLOSE);
}

void	do_heres(t_mini *mini)
{
	int		fd[2];
	char	*line;
	int		i;
	int		pid;

	i = 0;
	while (mini->tok_lex[i].word != NULL)
	{
		if (mini->tok_lex[i].type == HERE_DOC)
		{
			pipe(fd);
			mini->tok_lex[i].fd_here = fd[0];
			signals_here();
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				line = readline(">");
				while (line && ft_strncmp(line, mini->tok_lex[i].word, 0xFF))
				{
					write(fd[1], line, ft_strlen(line));
					write(fd[1], "\n", 1);
					free(line);
					line = readline(">");
				}
				exit(0);
			}
			waitpid(-1, NULL, 0);
			signals_mini();
			if (close(fd[1]) < 0)
				end(2, MINI, "close", CCLOSE);
		}
		++i;
	}
}

void	close_heres(t_mini *mini, int j)
{
	int	i;
	int	exit;

	exit = SUCCESS;
	i = mini->cmds[j].token_ini;
	while (i != mini->cmds[j].token_fi && exit == SUCCESS)
	{
		if (mini->tok_lex[i].type == PIPE)
		{
			if (close(mini->tok_lex[i].fd_here) < 0)
				end(2, MINI, "close", CCLOSE);
		}
		++i;
	}
}