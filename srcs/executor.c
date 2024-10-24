/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/10/20 14:48:39 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	result;
	int	in_cp;
	int	out_cp;

	if (cmd->in < 0 || cmd->out < 0)
		return ;
	in_cp = dup(STDIN_FILENO);
	out_cp = dup(STDOUT_FILENO);
	if (in_cp == -1 || out_cp == -1 || replace_io(cmd->in, cmd->out) == -1)
		return ;
	result = exec(cmd->cmd, envpp, cmd, 1);
	if (replace_io(in_cp, out_cp) == -1)
	{
		freecmd(cmd);
		free2(*envpp);
		shell_exit(GENERAL_ERR);
	}
	set_exit_code(result, 0);
}

static void	executor_child_process(t_cmd_table *cmd, char ***envpp)
{
	int	result;

	if (cmd->pid == -1)
	{
		perror(NULL);
		set_exit_code(GENERAL_ERR, 0);
	}
	else if (cmd->pid == 0)
	{
		freecmd(cmd->next);
		cmd->next = NULL;
		if (cmd->in < 0 || cmd->out < 0 || replace_io(cmd->in, cmd->out) == -1)
			exit(GENERAL_ERR);
		result = exec(cmd->cmd, envpp, cmd, 0);
		if (result != 0)
		{
			if (errno)
				ft_dprintf(2, "minishell: %s: %s\n",
					cmd->cmd[0], strerror(errno));
			exit(result);
		}
		exit(EXIT_SUCCESS);
	}
}

static void	handle_wstatus(int wstatus, int is_terminated)
{
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGINT)
		{
			set_exit_code(MANUAL_TERM, 0);
			printf("\n");
		}
		if (WTERMSIG(wstatus) == SIGQUIT)
		{
			set_exit_code(MANUAL_QUIT, 0);
			printf("Quit (core dumped)\n");
		}
		return ;
	}
	else if (is_terminated)
		printf("\n");
	set_exit_code(WEXITSTATUS(wstatus), 0);
}

static void	executor_fork(t_cmd_table *cmd, char ***envpp)
{
	t_cmd_table	*cmd_start;
	int			wstatus;
	int			is_terminated;

	cmd_start = cmd;
	while (cmd && cmd->cmd[0])
	{
		cmd->pid = fork();
		executor_child_process(cmd, envpp);
		close_opened_io(cmd->in, cmd->out);
		cmd = cmd->next;
	}
	set_signal(S_DISABLE);
	cmd = cmd_start;
	wstatus = 0;
	is_terminated = 0;
	while (cmd && cmd->cmd[0])
	{
		waitpid(cmd->pid, &wstatus, 0);
		if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
			is_terminated = 1;
		cmd = cmd->next;
	}
	set_signal(S_ENABLE);
	handle_wstatus(wstatus, is_terminated);
}

void	executor(t_cmd_table *cmd, char ***envpp)
{
	if (!cmd)
	{
		if (errno && errno != ENOTTY)
		{
			ft_dprintf(2, "minishell: %s\n", strerror(errno));
			errno = 0;
			set_exit_code(GENERAL_ERR, 0);
		}
		return ;
	}
	mod_sigquit_key(S_RESTORE);
	if (cmd->next == NULL && cmd->cmd[0] && is_builtin(cmd->cmd[0]))
		executor_nofork(cmd, envpp);
	else
		executor_fork(cmd, envpp);
	mod_sigquit_key(S_DISABLE);
}
