/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:26:35 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/29 18:28:08 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	read_and_process_line(int pipefd, char *delimiter, char **envp);

int	handle_heredoc(char *delimiter, char **envp)
{
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		status = read_and_process_line(pipefd[1], delimiter, envp);
		if (status <= 0)
			break ;
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	output_redirection(t_cmd_table *current, t_redirection *tmp)
{
	if (current->out != STDOUT_FILENO)
		close(current->out);
	if (ft_strcmp(tmp->op, ">") == 0)
		current->out = open(tmp->fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		current->out = open(tmp->fd_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (current->out == -1)
	{
		ft_dprintf(2, " %s\n", strerror(errno));
		errno = 0;
		g_exit_code = 1;
		return (-1);
	}
	return (0);
}

int	input_redirection(t_cmd_table *current, t_redirection *tmp, char **envp)
{
	if (current->in != STDIN_FILENO)
		close(current->in);
	if (ft_strcmp(tmp->op, "<") == 0)
		current->in = open(tmp->fd_name, O_RDONLY);
	else
		current->in = handle_heredoc(tmp->fd_name, envp);
	if (current->in == -1)
	{
		ft_dprintf(2, " %s\n", strerror(errno));
		errno = 0;
		g_exit_code = 1;
		return (-1);
	}
	return (0);
}

int	handle_redirection(t_cmd_table *current, char **envp)
{
	t_redirection	*tmp;

	tmp = current->redir;
	while (tmp)
	{
		if (ft_strcmp(tmp->op, ">") == 0 || ft_strcmp(tmp->op, ">>") == 0)
		{
			if (output_redirection(current, tmp) == -1)
				return (-1);
		}
		else if (ft_strcmp(tmp->op, "<") == 0 || ft_strcmp(tmp->op, "<<") == 0)
		{
			if (input_redirection(current, tmp, envp) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_cmd_table	*exec_preparator(t_cmd_table *cmds, char **envp)
{
	t_cmd_table		*head;
	t_cmd_table		*current;

	current = cmds;
	head = NULL;
	head = current;
	while (current)
	{
		if (current->redir)
			handle_redirection(current, envp);
		free_redirections(current->redir);
		if (!current->next)
			break ;
		if (current->next)
			handle_pipe(&current);
	}
	return (head);
}
