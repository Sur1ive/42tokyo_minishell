/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:07:41 by yxu               #+#    #+#             */
/*   Updated: 2024/08/01 13:23:07 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_valid_env(char *name)
// {


// }

int	export(char **args, char ***envpp)
{
	char	*name;
	char	*value;

	name = args[1];
	value = args[2];
	ft_setenv(envpp, name, value);
	return (0);
}
