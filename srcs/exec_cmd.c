/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/08/03 19:01:27 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *command);
static int	exec_bulitin(char **args, char ***envpp);
static char	*search_executale(char *command, char *filepath_dest, char *path);
static int	exec_extern(char **args, char **envp);
int			exec_cmd(char **args, char ***envpp);

int	exec_cmd(char **args, char ***envpp)
{
	char	*command;

	command = args[0];
	if (is_builtin(command))
		exec_bulitin(args, envpp);
	else
		exec_extern(args, *envpp);
	return (0);
}

static int	is_builtin(char *command)
{
	if (!(ft_strcmp(command, "echo") && ft_strcmp(command, "pwd")
			&& ft_strcmp(command, "env") && ft_strcmp(command, "cd")
			&& ft_strcmp(command, "export") && ft_strcmp(command, "unset")))
		return (1);
	return (0);
}

static int	exec_bulitin(char **args, char ***envpp)
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
	return (-1);
}

static char	*search_executale(char *command, char *filepath_dest, char *path)
{
	char		*filepath_malloc;
	char		**dirs;
	int			i;
	struct stat	st;

	dirs = ft_split(path, ':');
	if (dirs == NULL)
		return (NULL);
	i = 0;
	while (dirs && dirs[i] != NULL)
	{
		filepath_malloc = ft_strjoin3(dirs[i++], "/", command);
		ft_memset(filepath_dest, 0, PATH_MAX + 1);
		ft_memcpy(filepath_dest, filepath_malloc, ft_strlen(filepath_malloc));
		free(filepath_malloc);
		if (stat(filepath_dest, &st) == 0)
		{
			free2(dirs);
			return (filepath_dest);
		}
	}
	free2(dirs);
	return (NULL);
}

static int	exec_extern(char **args, char **envp)
{
	char	filepath[PATH_MAX + 1];
	pid_t	pid;

	if (search_executale(args[0], filepath, ft_getenv(envp, "PATH")) == NULL)
	{
		printf("%s: command not found\n", args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(filepath, args, envp) != 0)
			printf("minishell: %s: %s\n", filepath, strerror(errno));
		exit(0);
	}
	else
	{
		wait(NULL);
		return (0);
	}
	return (0);
}
