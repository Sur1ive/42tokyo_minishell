/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:27:46 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/10/26 15:06:55 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

void	free_redirections(t_redirection **redirp)
{
	t_redirection	*tmp;
	t_redirection	*redir;

	if (redirp == NULL)
		return ;
	redir = *redirp;
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
	*redirp = NULL;
}

int	print_syntax_error(char *token)
{
	ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n",
		token);
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
