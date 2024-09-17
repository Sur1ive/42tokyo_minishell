/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/09/17 22:41:50 by yxu              ###   ########.fr       */
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

void	printcmd(t_cmd_table *tab)
{
	int		i;
	char	**cmd;

	cmd = tab->cmd;
	if (!cmd)
		return ;
	i = 0;
	printf("------------------test--------------------\n");
	printf("cmd: ");
	while (cmd[i])
		printf("%s, ", cmd[i++]);
	printf("\n");
	printf("next: %p, in: %d, out: %d\n", tab->next, tab->in, tab->out);
	printf("------------------------------------------\n");
}

void	executor(t_cmd_table *cmd, char ***envpp)
{
	pid_t	pid;
	int		result;

	if (cmd && cmd->next == NULL && cmd->cmd[0] && is_builtin(cmd->cmd[0]))
	{
		result = exec_bulitin((cmd->cmd), envpp);
		if (result < 0)
		{
			freecmd(cmd);
			free2(*envpp);
			exit(g_exit_code);
		}
		g_exit_code = result;
		return ;
	}
	while (cmd && cmd->cmd[0])
	{
		// printcmd(cmd);
		pid = fork();
		if (pid == -1)
		{
			printf("minishell: %s\n", strerror(errno));
			g_exit_code = 1;
		}
		if (pid == 0)
		{
			if (cmd->in != 0)
			{
				dup2(cmd->in, STDIN_FILENO);
				close(cmd->in);
			}
			if (cmd->out != 1)
			{
				dup2(cmd->out, STDOUT_FILENO);
				close(cmd->out);
			}
			if (exec(cmd->cmd, envpp) != 0)
			{
				if (errno)
					printf("minishell: %s\n", strerror(errno));
				exit(GENERAL_ERR);
			}
			exit(EXIT_SUCCESS);
		}
		else
			wait(&g_exit_code);
		cmd = cmd->next;
	}
	return ;
}
