/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:33:38 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/10/23 16:19:03 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	create_pipe(int *pipefd, int mode)
{
	static int	count = 0;

	if (mode == PIPECOUNTRESET)
	{
		count = 0;
		return (0);
	}
	if (count >= PIPEMAX)
	{
		print_syntax_error("|");
		return (-1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		errno = 0;
		return (-1);
	}
	count++;
	return (1);
}

int	handle_pipe(t_cmd_table **current)
{
	int	pipefd[2];

	if (create_pipe(pipefd, CREATE) == -1)
		return (-1);
	if ((*current)->out == STDOUT_FILENO)
	{
		(*current)->out = pipefd[1];
	}
	else
		close(pipefd[1]);
	(*current)->next->prev = *current;
	*current = (*current)->next;
	(*current)->in = pipefd[0];
	return (0);
}
