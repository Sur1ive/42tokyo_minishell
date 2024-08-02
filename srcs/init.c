/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:38:38 by yxu               #+#    #+#             */
/*   Updated: 2024/08/02 14:07:16 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_envp(char ***envpp)
{
	int		flag;
	char	workdir[PATH_MAX + 1];

	*envpp = NULL;
	ft_memset(workdir, 0, PATH_MAX + 1);
	flag = 0;
	flag += ft_setenv(envpp, "PWD", getcwd(workdir, PATH_MAX));
	if (flag < 0)
	{
		printf("minishell: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}
