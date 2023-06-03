/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:20:45 by baltes-g          #+#    #+#             */
/*   Updated: 2023/06/03 19:40:53 by baltes-g         ###   ########.fr       */
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
# include <string.h>
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
	unsigned char	exit;
	int				sigint;
	int				sigquit;
	int				n_nodes;
	pid_t			pid;
}	t_signal;

typedef struct s_token
{
	char*			word;
	int				expand;
	enum e_type		type;
	struct s_token	*next;
}	t_token;

typedef struct s_node_env
{
	char				*data;
	char				*value;
	struct s_node_env	*prev;
	struct s_node_env	*next;
}	t_node_env;

typedef struct s_env
{
	t_node_env	*first;
	t_node_env	*last;
	int			size;
}	t_env;

typedef struct s_simple_cmd
{
	char	**args;
	int		token_ini;
	int		token_fi;
	pid_t	pid;

}	t_simple_cmd;

typedef struct s_mini
{
	t_env			*env;
	t_token			*tok;
	t_token			*tok_lex;
	char			*cmdline;
	t_simple_cmd	*cmds;
	int				n_cmds;
}	t_mini;

//ENV
char		*search_env(t_env *env, const char *s);
void		create_env(t_env *env, char **splited);
void		mod_env(t_env *env, const char *s, char *m);
void		init_env(t_mini *mini, char **env);
char		*get_env_var(t_env *env, const char *s);
char		**env_to_str(t_env *env);

//BUILT-INS
int			exec_env(t_env *env);
int			exec_pwd(t_env *env);
int			exec_cd(t_mini *mini, char **args);
int			exec_exit(t_mini *mini, char *num);
int			exec_export(t_env *env, char *args);
int			exec_unset(t_env *env, char *arg);

//PARSER

void 		lexer(t_mini *mini);
t_token*	ft_split_tokens(char *s);
void		ft_check_escaped(char *str);
int			ft_isquote(char *s, char quote);
int			ft_isscaped(char *s);
enum e_type	choose_type(char *word);
void		assing_type(t_token *tokens);
int			reserved(char *str);
int			assing_input(t_token *tokens, int i);
int			assing_output(t_token *tokens, int i);
int			assing_output_append(t_token *tokens, int i);
int			assing_heredoc(t_token *tokens, int i);
int			assing_command(t_token *tokens, int i);
void		syntax(t_mini *mini);
void		get_args(t_mini *mini, int ini, int fi, int k);	
void		expand(t_mini *mini);

//EXEC
void	exec(t_mini *mini);
char	*get_path(char **envp, char *exe);
void	redir_pipes(t_mini *mini, int *p, int i);
void	redir_files(t_mini *mini, int i);

//UTILS

int		ft_strcmp(const char *s1, const char *s2);
int		count_env(t_env *env);
void	set_exec(t_env *env, char *value);

//SIGNALS

void		set_signals(void);

extern t_signal	g_sig;
#endif
