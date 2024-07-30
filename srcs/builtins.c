/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:19:07 by yxu               #+#    #+#             */
/*   Updated: 2024/07/30 11:35:12 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (i > 0)
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
		return (1);
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
	if (!args)
		chdir(getenv("HOME"));
	else if (args[1])
	{
		printf("cd: too many args\n");
		return (1);
	}
	else
	{
		chdir(args[0]);
	}
	return (0);
}
