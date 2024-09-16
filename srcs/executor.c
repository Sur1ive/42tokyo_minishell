/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/09/16 21:26:31 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table	*parseline_for_test(char *line)
{
	t_cmd_table	*cmd;

	cmd = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	cmd->cmd = ft_split(line, ' ');
	cmd->next = NULL;
	return (cmd);
}

void	freecmd_for_test(t_cmd_table *cmd)
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

int	executor(t_cmd_table *cmd, char ***envpp)
{
	pid_t	pid;

	if (cmd && cmd->next == NULL && cmd->cmd[0] && is_builtin(cmd->cmd[0]))
	{
		exec_bulitin((cmd->cmd), envpp);
		return (0);
	}
	while (cmd && cmd->cmd[0])
	{
		pid = fork();
		if (pid == -1)
		{
			printf("minishell: %s\n", strerror(errno));
			freecmd_for_test(cmd);
			free2(*envpp);
			exit(errno);
		}
		if (pid == 0)
		{
			if (exec(cmd->cmd, envpp) != 0 && errno)
			{
				printf("minishell: %s\n", strerror(errno));
				freecmd_for_test(cmd);
				exit(errno);
			}
			freecmd_for_test(cmd);
			exit(EXIT_SUCCESS);
		}
		else
			wait(NULL);
		cmd = cmd->next;
	}
	return (0);
}
