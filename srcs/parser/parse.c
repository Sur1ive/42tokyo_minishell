/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:37 by yxu               #+#    #+#             */
/*   Updated: 2024/10/06 12:18:09 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

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
	return (cmd_table);
}
