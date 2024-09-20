/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/09/20 17:09:55 by yxu              ###   ########.fr       */
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

// static void	printcmd(t_cmd_table *tab)
// {
// 	int		i;
// 	char	**cmd;

// 	cmd = tab->cmd;
// 	if (!cmd)
// 		return ;
// 	i = 0;
// 	printf("------------------test--------------------\n");
// 	printf("cmd: ");
// 	while (cmd[i])
// 		printf("%s, ", cmd[i++]);
// 	printf("\n");
// 	printf("next: %p, in: %d, out: %d\n", tab->next, tab->in, tab->out);
// 	printf("------------------------------------------\n");
// }

static void	executor_nofork(t_cmd_table *cmd, char ***envpp)
{
	int		result;

	result = exec_bulitin((cmd->cmd), envpp);
	if (result < 0)
	{
		freecmd(cmd);
		free2(*envpp);
		exit(result * -1 % 256);
	}
	g_exit_code = result;
}

static void	executor_child_process(t_cmd_table *cmd, char ***envpp)
{
	int	result1;
	int	result2;

	if (cmd->in != 0)
	{
		result1 = dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != 1)
	{
		result2 = dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	if (result1 == -1 || result2 == -1)
	{
		printf("minishell: %s\n", strerror(errno));
		exit(GENERAL_ERR);
	}
	if (exec(cmd->cmd, envpp) != 0)
	{
		if (errno)
			printf("minishell: %s\n", strerror(errno));
		exit(GENERAL_ERR);
	}
	exit(EXIT_SUCCESS);
}

static void	executor_fork(t_cmd_table *cmd, char ***envpp)
{
	pid_t	pid;
	int		wstatus;

	while (cmd && cmd->cmd[0])
	{
		pid = fork();
		if (pid == -1)
		{
			printf("minishell: %s\n", strerror(errno));
			g_exit_code = 1;
		}
		if (pid == 0)
			executor_child_process(cmd, envpp);
		else
			wait(&wstatus);
		g_exit_code = WEXITSTATUS(wstatus);
		if (cmd->in != 0)
			close(cmd->in);
		if (cmd->out != 1)
			close(cmd->out);
		cmd = cmd->next;
	}
}

void	executor(t_cmd_table *cmd, char ***envpp)
{
	if (cmd->next == NULL && cmd->cmd[0] && is_builtin(cmd->cmd[0]))
		executor_nofork(cmd, envpp);
	else
		executor_fork(cmd, envpp);
}
