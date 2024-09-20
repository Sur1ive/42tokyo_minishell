/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:52:08 by yxu               #+#    #+#             */
/*   Updated: 2024/09/20 14:08:50 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (0);
	while (envp[i])
	{
		if (envp[i][0] != '\0')
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
