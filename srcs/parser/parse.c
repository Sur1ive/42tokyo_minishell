/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:37 by yxu               #+#    #+#             */
/*   Updated: 2024/09/28 05:09:03 by nakagawashi      ###   ########.fr       */
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
	if (ft_strcmp(command[0], "|") == 0)
	{
		ft_dprintf(2, " syntax error near unexpected token `%s'\n", command[0]);
		g_exit_code = MISUSE_OF_BUILTINS;
		free2(command);
		return (NULL);
	}
	cmd_table = parser(command);
	cmd_table = expand_envs(cmd_table, envp);
	free2(command);
	if (!cmd_table)
		return (NULL);
	cmd_table = exec_preparator(cmd_table);
	return (cmd_table);
}
