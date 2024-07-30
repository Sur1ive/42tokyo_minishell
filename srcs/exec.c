/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/07/30 11:10:31 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *command);
static int	exec_bulitin(char *command, char **args, char **envp);
int			exec_extern(char *command, char **args, char **envp);
int			exec(char **commandline, char **envp);

int	exec(char **commandline, char **envp)
{
	char	*command;
	char	**args;

	command = commandline[0];
	if (command == NULL)
		return (0);
	args = commandline + 1;
	if (is_builtin(command))
		exec_bulitin(command, args, envp);
	else
		exec_extern(command, args, envp);
	free2(commandline);
	return (0);
}

static int	is_builtin(char *command)
{
	if (!(ft_strcmp(command, "echo") && ft_strcmp(command, "pwd")
			&& ft_strcmp(command, "env")))
		return (1);
	return (0);
}

static int	exec_bulitin(char *command, char **args, char **envp)
{
	if (ft_strcmp(command, "echo") == 0)
		return (echo(args));
	if (ft_strcmp(command, "pwd") == 0)
		return (pwd());
	if (ft_strcmp(command, "env") == 0)
		return (env(envp));
	return (-1);
}

int	exec_extern(char *command, char **args, char **envp)
{
	char	*path_env;
	char	**dirs;
	char	*path;
	char	*filepath;
	int		i;
	pid_t	pid;

	path_env = getenv("PATH");
	dirs = ft_split(path_env, ':');
	i = 0;
	while (dirs[i] != NULL)
	{
		path = ft_strjoin(dirs[i++], "/");
		filepath = ft_strjoin(path, command);
		free(path);
		if (access(filepath, X_OK) == 0)
		{
			free2(dirs);
			pid = fork();
			if (pid == 0)
			{
				execve(filepath, args, envp);
			}
			else
			{
				wait(NULL);
				free(filepath);
				return (0);
			}
		}
		free(filepath);
	}
	free2(dirs);
	printf("%s: command not found\n", command);
	return (127);
}
