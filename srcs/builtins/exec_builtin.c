/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:53:13 by yxu               #+#    #+#             */
/*   Updated: 2024/10/02 22:46:23 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (!(ft_strcmp(command, "echo") && ft_strcmp(command, "pwd")
			&& ft_strcmp(command, "env") && ft_strcmp(command, "cd")
			&& ft_strcmp(command, "export") && ft_strcmp(command, "unset")
			&& ft_strcmp(command, "exit")))
		return (1);
	return (0);
}

int	exec_builtin(char **args, char ***envpp, pid_t pid)
{
	char	*command;

	command = args[0];
	if (ft_strcmp(command, "echo") == 0)
		return (echo(args));
	if (ft_strcmp(command, "pwd") == 0)
		return (pwd());
	if (ft_strcmp(command, "env") == 0)
		return (env(*envpp));
	if (ft_strcmp(command, "cd") == 0)
		return (cd(args, envpp));
	if (ft_strcmp(command, "export") == 0)
		return (export(args, envpp));
	if (ft_strcmp(command, "unset") == 0)
		return (unset(args, envpp));
	if (ft_strcmp(command, "exit") == 0)
		return (builtin_exit(args, pid));
	return (CMD_NOT_FOUND);
}
