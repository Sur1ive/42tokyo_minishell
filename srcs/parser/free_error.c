/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:27:46 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/10/07 20:06:03 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

void	free_redirections(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->op)
			free(tmp->op);
		if (tmp->fd_name)
			free(tmp->fd_name);
		free(tmp);
	}
}

void	free_table(t_cmd_table *table)
{
	t_cmd_table	*tmp;

	while (table)
	{
		tmp = table;
		table = table->next;
		if (tmp->redir)
			free_redirections(tmp->redir);
		if (tmp->cmd)
			free2(tmp->cmd);
		free(tmp);
	}
}

static int	print_syntax_error(char *token)
{
	ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n", token);
	set_exit_code(MISUSE_OF_BUILTINS, 0);
	return (-1);
}

int	syntax_error(char **cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd[0], "|") == 0)
		return (print_syntax_error(cmd[0]));
	while (cmd[i])
	{
		if (is_redirection(cmd[i]))
		{
			if (!cmd[i + 1])
				return (print_syntax_error("newline"));
			if (is_redirection(cmd[i + 1]) || ft_strcmp(cmd[i + 1], "|") == 0)
				return (print_syntax_error(cmd[i + 1]));
		}
		else if (!ft_strcmp(cmd[i], "|"))
		{
			if (!cmd[i + 1])
				return (print_syntax_error("newline"));
			if (ft_strcmp(cmd[i + 1], "|") == 0)
				return (print_syntax_error(cmd[i + 1]));
		}
		i++;
	}
	return (1);
}
