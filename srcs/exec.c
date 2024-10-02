/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:36:14 by yxu               #+#    #+#             */
/*   Updated: 2024/10/02 23:14:56 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_executable(char *command, char *filepath_dest, char *path)
{
	char		*filepath_malloc;
	char		**dirs;
	int			i;
	struct stat	st;

	if (path == NULL)
		path = ".";
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
		if (stat(filepath_dest, &st) == 0 && S_ISREG(st.st_mode))
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
		if (ft_getenv(envp, "PATH") == NULL)
			ft_dprintf(2, "minishell: %s: No such file or directory\n",
				args[0]);
		else
			ft_dprintf(2, "%s: command not found\n", args[0]);
		exit(CMD_NOT_FOUND);
	}
	execve(filepath, args, envp);
	if (errno == EACCES)
	{
		ft_dprintf(2, "bash: %s: Permission denied\n", filepath);
		errno = 0;
		exit(CANNOT_EXEC);
	}
	return (GENERAL_ERR);
}

static int	exec_cmd(char **args, char ***envpp, pid_t pid)
{
	char	*command;

	command = args[0];
	if (is_builtin(command))
		return (exec_builtin(args, envpp, pid));
	else
		return (exec_extern(args, *envpp));
}

static int	exec_dir(char **args, char ***envpp)
{
	struct stat	st;

	if (ft_strcmp(args[0], ".") * ft_strcmp(args[0], "..") == 0)
	{
		ft_dprintf(2, "%s: command not found\n", args[0]);
		exit(CMD_NOT_FOUND);
	}
	if (stat(args[0], &st))
	{
		if (errno == ENOENT)
			return (CMD_NOT_FOUND);
		return (GENERAL_ERR);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_dprintf(2, "minishell: %s: Is a directory\n", args[0]);
		exit(CANNOT_EXEC);
	}
	return (execve(args[0], args, *envpp));
}

int	exec(char **args, char ***envpp, t_cmd_table *cmd, pid_t pid)
{
	int	result;

	if (args == NULL || args[0] == NULL)
		return (0);
	if (ft_strchr(args[0], '/') != NULL)
	{
		result = exec_dir(args, envpp);
		if (errno == EACCES)
			return (CANNOT_EXEC);
	}
	else
		result = exec_cmd(args, envpp, pid);
	if (result < 0)
	{
		freecmd(cmd);
		free2(*envpp);
		shell_exit(result * -1 % 256);
	}
	return (result);
}
