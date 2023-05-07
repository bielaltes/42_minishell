/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:20:45 by baltes-g          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/07 10:55:36 by baltes-g         ###   ########.fr       */
=======
/*   Updated: 2023/05/07 17:22:48 by jsebasti         ###   ########.fr       */
>>>>>>> a3810705f0d956f89c6b65277ec72a6db885e468
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

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

<<<<<<< HEAD
typedef struct s_cmdline
{
    t_env   *env;
    t_token *tok;
    int     in;
    int     out;
    int     pid;
}   t_cmdline;
=======
typedef struct	s_env
{
	char			*word;
}	t_env;
>>>>>>> a3810705f0d956f89c6b65277ec72a6db885e468

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
	int		ext;
	int		pid;
}	t_mini;

void	init_env(t_mini *mini, char **env);

#endif
