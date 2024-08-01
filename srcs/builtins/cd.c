/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:52:04 by yxu               #+#    #+#             */
/*   Updated: 2024/08/01 21:54:19 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setpwdenv(char ***envpp)
{
	char	workdir[PATH_MAX + 1];

	ft_memset(workdir, 0, PATH_MAX + 1);
	if (getcwd(workdir, PATH_MAX) == NULL)
	{
		printf("bash: cd: %s\n", strerror(errno));
		return (-1);
	}
	if (ft_setenv(envpp, "PWD", workdir) == -1)
	{
		printf("bash: cd: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

int	cd(char **args, char ***envpp)
{
	char	*dir;

	if (args[1] == NULL)
		dir = ft_getenv(*envpp, "HOME");
	else if (args[2])
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	else
		dir = args[1];
	if (chdir(dir) == -1)
	{
		printf("bash: cd: %s: %s\n", dir, strerror(errno));
		return (1);
	}
	if (setpwdenv(envpp) == -1)
	{
		printf("bash: cd: %s: %s\n", dir, strerror(errno));
		return (1);
	}
	return (0);
}
