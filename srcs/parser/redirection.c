/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:26:35 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/26 11:48:45 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;
	size_t	len;

	len = 0;
	line = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	ft_printf("heredoc> ");
	while (ft_getline(&line, &len) != -1)
	{
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		ft_printf("heredoc> ");
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	count_arg(char **command)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (command[i] && ft_strcmp(command[i], "|") != 0)
	{
		if (command[i + 1] && is_redirection(command[i]))
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

int	handle_redirection(t_cmd_table *current, t_parsed_cmd *p_current)
{
	t_redirection	*tmp;

	tmp = p_current->redir;
	while (tmp)
	{
		if (ft_strcmp(tmp->op, ">") == 0)
			current->out = open(tmp->fd_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(tmp->op, ">>") == 0)
			current->out = open(tmp->fd_name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (ft_strcmp(tmp->op, "<") == 0)
			current->in = open(tmp->fd_name, O_RDONLY);
		else if (ft_strcmp(tmp->op, "<<") == 0)
			current->in = handle_heredoc(tmp->fd_name);
		if (current->out == -1 || current->in == -1)
		{
			ft_dprintf(2, "%s\n", strerror(errno));
			errno = 0;
			g_exit_code = 1;
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	handle_pipe(t_cmd_table **current, t_parsed_cmd *p_current)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	(*current)->out = pipefd[1];
	(*current)->next = create_cmd_table_entry(p_current->next);
	if ((*current)->next == NULL)
		return (-1);
	(*current)->next->prev = *current;
	*current = (*current)->next;
	(*current)->in = pipefd[0];
	return (0);
}

t_cmd_table	*exec_preparator(t_parsed_cmd *cmds)
{
	t_cmd_table		*head;
	t_cmd_table		*current;
	t_parsed_cmd	*p_current;

	p_current = cmds;
	head = NULL;
	current = create_cmd_table_entry(p_current);
	if (!current)
		return (NULL);
	head = current;
	while (p_current)
	{
		if (p_current->redir)
			handle_redirection(current, p_current);
		if (p_current->next)
			handle_pipe(&current, p_current);
		p_current = p_current->next;
	}
	return (head);
}
