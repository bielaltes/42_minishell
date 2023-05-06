/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:20:45 by baltes-g          #+#    #+#             */
/*   Updated: 2023/05/06 20:04:05 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env
{
    char    *word;
    t_env   *next;
}   t_env;

typedef struct  s_token
{
    char*   word;
    enum    type;
    t_token *next;
}       t_token;

typedef struct s_mini
{
    t_env   *env;
    t_token *tok;
    int     in;
    int     out;
    int     pid;
}   t_mini;

#endif