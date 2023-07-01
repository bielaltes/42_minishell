/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:04:28 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 11:34:04 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_here(int fd)
{
	if (dup2(fd, 0) < 0)
		return (FAILURE);
	return (SUCCESS);
}

static int	do_heres_while(t_mini *mini, int i, char *line, int fd[2])
{
	int		status;
	int		pid;

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
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
		return (FAILURE);
	signals_mini();
	return (SUCCESS);
}

int	do_heres(t_mini *mini)
{
	int		i;
	int		fd[2];
	char	*line;

	i = 0;
	line = NULL;
	while (mini->tok_lex[i].word != NULL)
	{
		if (mini->tok_lex[i].type == HERE_DOC)
		{
			if (do_heres_while(mini, i, line, fd) == FAILURE)
				return (FAILURE);
			if (close(fd[1]) < 0)
				end(2, MINI, "close", CCLOSE);
		}
		++i;
	}
	return (SUCCESS);
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
