/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:28:57 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/30 18:57:12 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	malloc_current_cmds(t_cmd_table *current, char **cmds, int i)
{
	if (current->cmd == NULL)
	{
		current->cmd = malloc(sizeof(char *) * (count_arg(&cmds[i]) + 1));
		if (current->cmd == NULL)
			return (-1);
	}
	return (0);
}

int	create_next_cmd(t_cmd_table **current, int *index)
{
	(*current)->cmd[*index] = NULL;
	*index = 0;
	(*current)->next = create_cmd_table_entry();
	if (!(*current)->next)
	{
		return (-1);
	}
	*current = (*current)->next;
	return (0);
}

int	create_redirection(t_redirection **redir, char **cmds, int *i)
{
	t_redirection	*tmp;
	t_redirection	*last;

	tmp = malloc(sizeof(t_redirection));
	if (!tmp)
		return (-1);
	tmp->op = ft_strdup(cmds[*i]);
	tmp->fd_name = ft_strdup(cmds[*i + 1]);
	tmp->next = NULL;
	if (!tmp->op || !tmp->fd_name)
		return (-1);
	(*i)++;
	if (!*redir)
		*redir = tmp;
	else
	{
		last = *redir;
		while (last->next)
			last = last->next;
		last->next = tmp;
	}
	return (0);
}

static int	process_cmd(t_cmd_table **current, char **cmds, int *i, int *index)
{
	if (is_redirection(cmds[*i]))
		return (create_redirection(&((*current)->redir), cmds, i));
	if (ft_strcmp(cmds[*i], "|") == 0)
		return (create_next_cmd(current, index));
	(*current)->cmd[*index] = ft_strdup(cmds[*i]);
	if (!(*current)->cmd[(*index)++])
		return (-1);
	return (0);
}

t_cmd_table	*parser(char **cmds)
{
	t_cmd_table		*t_cmds;
	t_cmd_table		*current;
	int				i;
	int				index;

	i = 0;
	index = 0;
	t_cmds = create_cmd_table_entry();
	if (!t_cmds)
		return (NULL);
	current = t_cmds;
	while (cmds[i])
	{
		if (malloc_current_cmds(current, cmds, i) == -1)
			return (free_table(t_cmds), NULL);
		if (process_cmd(&current, cmds, &i, &index) == -1)
		{
			free_table(t_cmds);
			return (NULL);
		}
		i++;
	}
	current->cmd[index] = NULL;
	return (t_cmds);
}
