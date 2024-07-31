/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:19:07 by yxu               #+#    #+#             */
/*   Updated: 2024/07/31 11:22:16 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", args[i++]);
	}
	printf("\n");
	return (0);
}

int	pwd(void)
{
	char	workdir[PATH_MAX + 1];

	ft_memset(workdir, 0, PATH_MAX + 1);
	if (getcwd(workdir, PATH_MAX) == NULL)
	{
		printf("bash: pwd: %s\n", strerror(errno));
		return (1);
	}
	printf("%s\n", workdir);
	return (0);
}

int	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (0);
}

int	cd(char **args)
{
	char	*dir;

	if (args[1] == NULL)
		dir = getenv("HOME");
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
	return (0);
}
