/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:36:14 by yxu               #+#    #+#             */
/*   Updated: 2024/08/03 18:36:33 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_file(char **args, char ***envpp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, *envpp) != 0)
		{
			printf("minishell: %s\n", strerror(errno));
			return (-1);
		}
		return (0);
	}
	else
	{
		wait(NULL);
		return (0);
	}
}

int	exec(char **args, char ***envpp)
{
	struct stat	st;
	int			result;

	if (args[0] == NULL)
		return (0);
	if (stat(args[0], &st) == 0)
		result = exec_file(args, envpp);
	else
	{
		printf("minishell test: %s\n", strerror(errno));
		result = exec_cmd(args, envpp);
	}
	return (result);
}
