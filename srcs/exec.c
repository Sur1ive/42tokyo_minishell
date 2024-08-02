/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/08/02 12:15:40 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *command);
static int	exec_bulitin(char **args, char ***envpp);
static char	*search_executale(char *command, char *filepath_dest);
static int	exec_extern(char **args, char **envp);
int			exec(char **args, char ***envpp);

int	exec(char **args, char ***envpp)
{
	char	*command;

	command = args[0];
	if (command == NULL)
		return (0);
	if (is_builtin(command))
		exec_bulitin(args, envpp);
	else
		exec_extern(args, *envpp);
	free2(args);
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

static char	*search_executale(char *command, char *filepath_dest)
{
	char	*filepath_malloc;
	char	**dirs;
	int		i;
//search ./
	dirs = ft_split(getenv("PATH"), ':');
	i = 0;
	while (dirs[i] != NULL)
	{
		filepath_malloc = ft_strjoin3(dirs[i++], "/", command);
		ft_memset(filepath_dest, 0, PATH_MAX + 1);
		ft_memcpy(filepath_dest, filepath_malloc, ft_strlen(filepath_malloc));
		free(filepath_malloc);
		if (access(filepath_dest, X_OK) == 0)
		{
			free(dirs);
			return (filepath_dest);
		}
	}
	free(dirs);
	return (NULL);
}

int	exec_extern(char **args, char **envp)
{
	char	filepath[PATH_MAX + 1];
	pid_t	pid;

	if (search_executale(args[0], filepath) == NULL)
	{
		printf("%s: command not found\n", args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		execve(filepath, args, envp);
	else
	{
		wait(NULL);
		return (0);
	}
	return (0);
}
