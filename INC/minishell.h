/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:20:45 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/08 09:45:26 by baltes-g         ###   ########.fr       */
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
//# include <curses.h>
//# include <term.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

enum	e_type
{
	NONE,
	ARG,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_APP,
	OPEN_FILE,
	LIMITOR,
	EXIT_FILE,
	EXIT_FILE_APP,
	SYN_ERROR,
	ERROR,
};

typedef struct	s_token
{
	char*			word;
	enum e_type		type;
	int				expand;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char **env;
}	t_env;

typedef struct	s_mini
{
	t_env	*env;
	t_token	*tok;
	t_token *tok_lex;
	char * cmdline;
	int		in;
	int		out;
	int		ext;
	int		pid;
}	t_mini;

void	init_env(t_mini *mini, char **env);

//PARSER
void 	lexer(t_mini *mini);
t_token*	ft_split_tokens(char *s, char c);
void	ft_check_escaped(char *str);
int		ft_isquote(char *s, char quote);
int		ft_isscaped(char *s);
enum e_type choose_type(char *word);







#endif
