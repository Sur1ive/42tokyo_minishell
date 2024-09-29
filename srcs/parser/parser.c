/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:28:57 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/28 05:19:28 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	syntax_error(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (is_redirection(cmd[i]))
		{
			if (!cmd[i + 1])
			{
				ft_dprintf(2, " syntax error near unexpected token `newline'\n");
				g_exit_code = MISUSE_OF_BUILTINS;
				return (-1);
			}
			else if (is_redirection(cmd[i + 1]) || ft_strcmp(cmd[i + 1], "|") == 0)
			{
				ft_dprintf(2, " syntax error near unexpected token `%s'\n", cmd[i + 1]);
				g_exit_code = MISUSE_OF_BUILTINS;
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

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

t_cmd_table	*parser(char **cmds)
{
	t_cmd_table		*t_cmds;
	t_cmd_table		*current;
	int				i;
	int				index;
	int				flag;

	i = 0;
	index = 0;
	flag = 0;
	t_cmds = create_cmd_table_entry();
	if (!t_cmds)
		return (NULL);
	current = t_cmds;
	while (cmds[i])
	{
		if (malloc_current_cmds(current, cmds, i) == -1)
			return (NULL);
		if (is_redirection(cmds[i]))
			flag = create_redirection(&(current->redir), cmds, &i);
		else if (ft_strcmp(cmds[i], "|") == 0)
			flag = create_next_cmd(&current, &index);
		else
		{
			current->cmd[index++] = ft_strdup(cmds[i]);
			if (!current->cmd[index - 1])
				flag = -1;
		}
		if (flag == -1)
		{
			free_table(t_cmds);
			return (NULL);
		}
		i++;
	}
	current->cmd[index] = NULL;
	return (t_cmds);
}