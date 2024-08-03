/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:36:14 by yxu               #+#    #+#             */
/*   Updated: 2024/08/03 19:27:22 by yxu              ###   ########.fr       */
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
			exit(errno);
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
	if (ft_strchr(args[0], '/') != NULL)
	{
		stat(args[0], &st);
		if (S_ISDIR(st.st_mode))
		{
			printf("minishell test: %s: Is a directory\n", args[0]);
			return (-1);
		}
		result = exec_file(args, envpp);
	}
	else
		result = exec_cmd(args, envpp);
	return (result);
}
