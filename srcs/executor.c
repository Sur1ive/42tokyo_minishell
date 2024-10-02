/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:47:59 by yxu               #+#    #+#             */
/*   Updated: 2024/10/02 13:03:14 by yxu              ###   ########.fr       */
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

static int	replace_io(int in, int out)
{
	int	result1;
	int	result2;

	result1 = 0;
	result2 = 0;
	if (in != 0)
	{
		result1 = dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != 1)
	{
		result2 = dup2(out, STDOUT_FILENO);
		close(out);
	}
	if (result1 == -1 || result2 == -1)
	{
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
		errno = 0;
		return (-1);
	}
	return (0);
}

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
	result = exec(cmd->cmd, envpp, cmd);
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
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
		errno = 0;
		set_exit_code(GENERAL_ERR, 0);
	}
	else if (cmd->pid == 0)
	{
		if (cmd->next)
			close(cmd->next->in);
		if (cmd->in < 0 || cmd->out < 0 || replace_io(cmd->in, cmd->out) == -1)
			shell_exit(GENERAL_ERR);
		result = exec(cmd->cmd, envpp, cmd);
		if (result != 0)
		{
			if (errno)
				ft_dprintf(2, "minishell: %s: %s\n",
					cmd->cmd[0], strerror(errno));
			shell_exit(result);
		}
		shell_exit(EXIT_SUCCESS);
	}
}

static void	executor_fork(t_cmd_table *cmd, char ***envpp)
{
	t_cmd_table	*cmd_start;
	int			wstatus;

	cmd_start = cmd;
	while (cmd && cmd->cmd[0])
	{
		cmd->pid = fork();
		executor_child_process(cmd, envpp);
		if (cmd->in != 0)
			close(cmd->in);
		if (cmd->out != 1)
			close(cmd->out);
		cmd = cmd->next;
	}
	cmd = cmd_start;
	while (cmd && cmd->cmd[0])
	{
		waitpid(cmd->pid, &wstatus, 0);
		set_exit_code(WEXITSTATUS(wstatus), 0);
		cmd = cmd->next;
	}
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
	if (cmd->next == NULL && cmd->cmd[0] && is_builtin(cmd->cmd[0]))
		executor_nofork(cmd, envpp);
	else
		executor_fork(cmd, envpp);
}
