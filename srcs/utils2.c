/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:59:20 by yxu               #+#    #+#             */
/*   Updated: 2024/10/02 10:50:22 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freecmd(t_cmd_table *cmd)
{
	t_cmd_table	*next;

	while (cmd)
	{
		next = cmd->next;
		free2(cmd->cmd);
		free(cmd);
		cmd = next;
	}
}

char	**ft_strdup2(char **arr)
{
	char	**arr_cp;
	int		i;

	if (arr == NULL)
		return (NULL);
	arr_cp = (char **)malloc(sizeof(char *) * (ft_count(arr) + 1));
	if (arr_cp == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		arr_cp[i] = ft_strdup(arr[i]);
		if (arr_cp[i] == NULL)
		{
			free2(arr_cp);
			return (NULL);
		}
		i++;
	}
	arr_cp[i] = NULL;
	return (arr_cp);
}
