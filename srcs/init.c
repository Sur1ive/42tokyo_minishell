/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:38:38 by yxu               #+#    #+#             */
/*   Updated: 2024/08/02 11:12:31 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_envp(char ***envpp)
{
	int	flag;

	*envpp = NULL;
	flag = 0;
	flag += ft_setenv(envpp, "PWD", getenv("PWD"));
	flag += ft_setenv(envpp, "HOME", getenv("HOME"));
	if (flag < 0)
	{
		printf("minishell: cd: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}
