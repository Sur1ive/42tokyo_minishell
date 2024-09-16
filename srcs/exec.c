/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:36:14 by yxu               #+#    #+#             */
/*   Updated: 2024/09/16 19:15:36 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_executable(char *command, char *filepath_dest, char *path)
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

	if (search_executable(args[0], filepath, ft_getenv(envp, "PATH")) == NULL)
	{
		printf("%s: command not found\n", args[0]);
		return (127);
	}
	return (execve(filepath, args, envp));
}

static int	exec_cmd(char **args, char ***envpp)
{
	char	*command;

	command = args[0];
	if (is_builtin(command))
		exec_bulitin(args, envpp);
	else
		exec_extern(args, *envpp);
	return (0);
}

int	exec(char **args, char ***envpp)
{
	struct stat	st;
	int			result;

	if (args == NULL || args[0] == NULL)
		return (0);
	if (ft_strcmp(args[0], ".") * ft_strcmp(args[0], "..") == 0)
	{
		printf("%s: command not found\n", args[0]);
		return (-1);
	}
	if (ft_strchr(args[0], '/') != NULL)
	{
		stat(args[0], &st);
		if (S_ISDIR(st.st_mode))
		{
			printf("minishell: %s: Is a directory\n", args[0]);
			return (-1);
		}
		result = execve(args[0], args, *envpp);
	}
	else
		result = exec_cmd(args, envpp);
	return (result);
}
