/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:27:46 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/28 05:15:14 by nakagawashi      ###   ########.fr       */
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
