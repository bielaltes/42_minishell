/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:46:12 by jsebasti          #+#    #+#             */
/*   Updated: 2023/05/16 01:31:00 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	update_oldpwd(t_env *env)
// {
// 	char	*tmp;

// 	tmp = get_current_dir_name();
// 	while (ft_strncmp(env->data, "OLDPWD", 6))
// 		env = env->next;
// 	env->data = ft_strjoin("OLDPWD=", tmp);
// 	if (!env->data)
// 	{
// 		free(tmp);
// 		return (1);
// 	}
// 	free(tmp);
// 	while (env->prev)
// 		env = env->prev;
// 	return (0);
// }

// static int	change_path(t_env *env, int options)
// {
// 	char	*dir;

// 	dir == NULL;
// 	if (options == 0)
// 	{
// 		if (update_oldpwd(env))
// 			return (1);
// 		chdir()
// 	}
// 	if (options == 1)
// 	{
// 		if (update_oldpwd(env))
// 			return (1);
// 	}
// }

// int	exec_cd(t_env *env, char **args)
// {
// 	// char	*temp;
// 	// char	**splited;

// 	if (!args[1])
// 		return (change_path(env, 0));
// 	if (!ft_strncmp(args[1], "-", 1))
// 		return (change_path(env, 1));
// 	return (0);
// }