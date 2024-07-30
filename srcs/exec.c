/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/07/30 10:11:53 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *command);
static int	exec_bulitin(char *command, char **args);
// static int	exec_extern(char *command, char **args);
int			exec(char **commandline);

int	exec(char **commandline)
{
	char	*command;
	char	**args;

	command = commandline[0];
	if (command == NULL)
		return (0);
	args = commandline + 1;
	if (is_builtin(command))
		exec_bulitin(command, args);
	// else
	// 	exec_extern(command, args);
	free2(commandline);
	return (0);
}

static int	is_builtin(char *command)
{
	if (!(ft_strcmp(command, "echo") && ft_strcmp(command, "pwd")))
		return (1);
	return (0);
}

static int	exec_bulitin(char *command, char **args)
{
	if (ft_strcmp(command, "echo") == 0)
		return (echo(args));
	if (ft_strcmp(command, "pwd") == 0)
		return (pwd());
	return (-1);
}

// static int	exec_extern(char *command, char **args)
// {

// }
