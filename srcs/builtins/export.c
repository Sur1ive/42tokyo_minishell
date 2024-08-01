/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:07:41 by yxu               #+#    #+#             */
/*   Updated: 2024/08/01 22:14:44 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_valid_env(char *name)
// {


// }

int	export(char **args, char ***envpp)
{
	char	**env_item;
	char	*name;


	env_item = ft_getenv_item(*envpp, args[1]);

	*env_item = ft_strdup(args[1]);
	return (0);
}
