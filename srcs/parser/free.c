/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:27:46 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/26 10:23:08 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static void	free_redirections(t_redirection *redir)
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

void	free_p_table(t_parsed_cmd *table, int type)
{
	t_parsed_cmd *tmp;

	while (table)
	{
		tmp = table;
		table = table->next;
		if (tmp->redir)
			free_redirections(tmp->redir);
		if (tmp->cmds && type)
			free2(tmp->cmds);
		free(tmp);
	}
}