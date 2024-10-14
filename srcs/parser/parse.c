/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:37 by yxu               #+#    #+#             */
/*   Updated: 2024/10/14 11:58:07 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

t_cmd_table	*create_cmd_table_entry(void)
{
	t_cmd_table	*entry;

	entry = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!entry)
		return (NULL);
	entry->cmd = NULL;
	entry->redir = NULL;
	entry->in = STDIN_FILENO;
	entry->out = STDOUT_FILENO;
	entry->next = NULL;
	entry->prev = NULL;
	return (entry);
}

t_cmd_table	*parseline(char *line, char **envp)
{
	char			**command;
	t_cmd_table		*cmd_table;

	command = NULL;
	command = lexer(line, command);
	if (!command)
		return (NULL);
	if (syntax_error(command) == -1)
	{
		free2(command);
		return (NULL);
	}
	cmd_table = parser(command);
	cmd_table = expand_envs(cmd_table, envp);
	free2(command);
	if (!cmd_table)
		return (NULL);
	cmd_table = exec_preparator(cmd_table, envp);
	if (set_exit_code(0, EC_RDONLY) == MANUAL_TERM)
	{
		freecmd(cmd_table);
		return (NULL);
	}
	return (cmd_table);
}
