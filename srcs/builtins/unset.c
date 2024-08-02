/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:13:50 by yxu               #+#    #+#             */
/*   Updated: 2024/08/02 13:51:26 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char **args, char ***envpp)
{
	char	**env_item;
	int		i;

	i = 1;
	while (args[i])
	{
		env_item = ft_getenv_item(*envpp, args[i++]);
		if (env_item == NULL)
			continue ;
		*env_item[0] = '\0';
	}
	return (0);
}
