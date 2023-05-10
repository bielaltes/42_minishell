/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:20:45 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/10 15:24:53 by baltes-g         ###   ########.fr       */
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
	CMD,
	ARG,
	FT_FILE,
	HERE_DOC,
	REDIR_INP,
	REDIR_OUT,
	REDIR_HERE,
	REDIR_APPEND,
	PIPE,
	END,
};

typedef struct s_signal
{
	int		exit;
	int		sigint;
	int		sigout;
	pid_t	pid;
}	t_signal;

typedef struct	s_token
{
	char*			word;
	int				expand;
	enum e_type		type;
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
	char	*cmdline;
	int		in;
	int		out;
}	t_mini;

void	init_env(t_mini *mini, char **env);

//PARSER

void 		lexer(t_mini *mini);
t_token*	ft_split_tokens(char *s, char c);
void		ft_check_escaped(char *str);
int			ft_isquote(char *s, char quote);
int			ft_isscaped(char *s);
enum e_type	choose_type(char *word);
void    assing_type(t_token *tokens);
int reserved(char *str);
int assing_input(t_token *tokens, int i);
int assing_output(t_token *tokens, int i);
int assing_output_append(t_token *tokens, int i);
int assing_heredoc(t_token *tokens, int i);
int assing_command(t_token *tokens, int i);



//SIGNALS

void		set_signals(void);






#endif
