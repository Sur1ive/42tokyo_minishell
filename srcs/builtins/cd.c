/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:52:04 by yxu               #+#    #+#             */
/*   Updated: 2024/08/02 14:13:48 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setpwdenv(char ***envpp)
{
	char	workdir[PATH_MAX + 1];

	ft_memset(workdir, 0, PATH_MAX + 1);
	if (getcwd(workdir, PATH_MAX) == NULL)
	{
		printf("minishell: cd: %s\n", strerror(errno));
		return (-1);
	}
	if (ft_getenv_item(*envpp, "PWD") == NULL)
		return (0);
	if (ft_setenv(envpp, "PWD", workdir) == -1)
	{
		printf("minishell: cd: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

int	cd(char **args, char ***envpp)
{
	char	*dir;

	if (args[1] == NULL)
		dir = ".";
	else if (args[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	else
		dir = args[1];
	if (chdir(dir) == -1)
	{
		printf("minishell: cd: %s: %s\n", dir, strerror(errno));
		return (1);
	}
	if (setpwdenv(envpp) == -1)
	{
		printf("minishell: cd: %s: %s\n", dir, strerror(errno));
		return (1);
	}
	return (0);
}
