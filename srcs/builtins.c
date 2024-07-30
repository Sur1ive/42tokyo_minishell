/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:19:07 by yxu               #+#    #+#             */
/*   Updated: 2024/07/30 10:12:10 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	i;

	i = 0;
	while (args[i])
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
	char	workdir[256];

	ft_memset(workdir, 0, 256);
	if (getcwd(workdir, 255) == NULL)
		return (1);
	printf("%s\n", workdir);
	return (0);
}
