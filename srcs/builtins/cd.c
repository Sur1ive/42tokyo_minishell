/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:52:04 by yxu               #+#    #+#             */
/*   Updated: 2024/07/31 14:53:10 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
