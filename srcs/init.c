/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:38:38 by yxu               #+#    #+#             */
/*   Updated: 2024/08/01 21:39:08 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_envp(char ***envpp)
{
	*envpp = NULL;
	ft_setenv(envpp, "PWD", getenv("PWD"));
	ft_setenv(envpp, "HOME", getenv("HOME"));
	return (0);
}
