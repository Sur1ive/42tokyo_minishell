/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:26:35 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/10/20 13:30:34 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	set_heredoc(char **delimiter, char **envp);

int	handle_heredocs(t_cmd_table *current, char **envp, int *here_fd)
{
	t_redirection	*tmp;

	tmp = current->redir;
	while (tmp)
	{
		if (ft_strcmp(tmp->op, "<<") == 0)
		{
			if (*here_fd != STDOUT_FILENO)
				close(*here_fd);
			*here_fd = set_heredoc(&(tmp->fd_name), envp);
			if (*here_fd == MANUAL_TERM * -1)
				return (MANUAL_TERM * -1);
			if (*here_fd == -1)
			{
				ft_dprintf(2, "minishell: %s\n", strerror(errno));
				errno = 0;
				set_exit_code(GENERAL_ERR, 0);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
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
		ft_dprintf(2, "minishell: %s: %s\n", tmp->fd_name, strerror(errno));
		errno = 0;
		set_exit_code(GENERAL_ERR, 0);
		return (-1);
	}
	return (0);
}

int	input_redirection(t_cmd_table *current, t_redirection *tmp, int here_fd)
{
	if (current->in != STDIN_FILENO)
		close(current->in);
	if (ft_strcmp(tmp->op, "<") == 0)
		current->in = open(tmp->fd_name, O_RDONLY);
	else
		current->in = here_fd;
	if (current->in == -1)
	{
		ft_dprintf(2, "minishell: %s: %s\n", tmp->fd_name, strerror(errno));
		errno = 0;
		set_exit_code(GENERAL_ERR, 0);
		return (-1);
	}
	return (0);
}

int	handle_redirection(t_cmd_table *current, char **envp)
{
	t_redirection	*tmp;
	int				here_fd;
	int				heredoc_result;		

	here_fd = STDOUT_FILENO;
	heredoc_result = handle_heredocs(current, envp, &here_fd);
	if (heredoc_result < 0)
		return (heredoc_result);
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
			if (input_redirection(current, tmp, here_fd) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_cmd_table	*exec_preparator(t_cmd_table *cmds, char **envp)
{
	t_cmd_table		*current;

	current = cmds;
	while (current)
	{
		if (current->redir
			&& handle_redirection(current, envp) == MANUAL_TERM * -1)
		{
			freecmd(cmds);
			return (NULL);
		}
		free_redirections(current->redir);
		if (!current->next)
			break ;
		if (current->next && handle_pipe(&current) == -1)
		{
			freecmd(cmds);
			return (NULL);
		}
	}
	return (cmds);
}
