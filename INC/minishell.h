/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:20:45 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/07 16:18:54 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_env
{
	char			*word;
}	t_env;

typedef struct	s_token
{
	char*			word;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct	s_mini
{
	t_env	*env;
	t_token	*tok;
	int		in;
	int		out;
	int		pid;
}	t_mini;

void	init_env(t_mini *mini, char **env);

#endif
