/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/09/08 18:01:15 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_cmd_table *cmd, char ***envpp)
{
	while (cmd)
	{
		exec(cmd->cmd, envpp);
		cmd = cmd->next;
	}
	return (0);
}
