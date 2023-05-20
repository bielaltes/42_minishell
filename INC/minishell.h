/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:20:45 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/20 04:02:03 by jsebasti         ###   ########.fr       */
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
# include <limits.h>
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
	int		sigquit;
	int		n_nodes;
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
	char			*data;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_simple_cmd
{
	char	**args;
	int		token_ini;
	int		token_fi;
	pid_t	pid;

}	t_simple_cmd;

typedef struct	s_mini
{
	t_env			*env;
	t_token			*tok;
	t_token 		*tok_lex;
	char			*cmdline;
	t_simple_cmd	*cmds;
	int				n_cmds;
	char			**def_env;
}	t_mini;


//ENV
int			search_env(t_env *env, const char *s, int opt);
void		init_env(t_mini *mini, char **env);

//BUILT-INS
int			exec_env(t_env *env);
int			exec_pwd(t_env *env);
int			exec_cd(t_mini *mini);
int			exec_exit(t_mini *mini);

//PARSER

void 		lexer(t_mini *mini);
t_token*	ft_split_tokens(char *s, char c);
void		ft_check_escaped(char *str);
int			ft_isquote(char *s, char quote);
int			ft_isscaped(char *s);
enum e_type	choose_type(char *word);
void    	assing_type(t_token *tokens);
int 		reserved(char *str);
int 		assing_input(t_token *tokens, int i);
int 		assing_output(t_token *tokens, int i);
int 		assing_output_append(t_token *tokens, int i);
int 		assing_heredoc(t_token *tokens, int i);
int 		assing_command(t_token *tokens, int i);
void 		syntax(t_mini *mini);
void   		get_args(t_mini *mini, int ini, int fi, int k);	

//EXEC
void    exec(t_mini *mini);
char	*get_path(char **envp, char *exe);
void    redir_pipes(t_mini *mini, int *p, int i);
void    redir_files(t_mini *mini, int i);




//SIGNALS

void		set_signals(void);

extern t_signal g_sig;
#endif
