/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:39:10 by baltes-g          #+#    #+#             */
/*   Updated: 2023/07/01 10:41:03 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_built(int code, char **args, t_mini *mini)
{
	if (code == 1)
		return (exec_env(mini->env));
	if (code == 2)
		return (exec_cd(mini, args));
	if (code == 3)
		return (exec_pwd(mini->env));
	if (code == 4)
		return (exec_exit(mini, args));
	if (code == 5)
		return (exec_export(mini->env, args));
	if (code == 6)
		return (exec_unset(mini->env, args));
	if (code == 7)
		return (exec_echo(args));
	return (1);
}

int	is_built_in(char *cmd, int *code)
{
	if (!ft_strcmp(cmd, "env"))
		*code = 1;
	else if (!ft_strcmp(cmd, "cd"))
		*code = 2;
	else if (!ft_strcmp(cmd, "pwd"))
		*code = 3;
	else if (!ft_strcmp(cmd, "exit"))
		*code = 4;
	else if (!ft_strcmp(cmd, "export"))
		*code = 5;
	else if (!ft_strcmp(cmd, "unset"))
		*code = 6;
	else if (!ft_strcmp(cmd, "echo"))
		*code = 7;
	return (*code);
}

int	exec_builtin_alone(t_mini *mini, int code)
{
	if (redir_files(mini, 0) == SUCCESS)
		return (exec_built(code, mini->cmds[0].args, mini));
	else
		return (1);
}
