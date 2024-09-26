/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:28:57 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/26 11:44:48 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	syntax_error(char *cmd, char *next_cmd)
{
	if (!cmd)
		return (0);
	if (is_redirection(cmd))
	{
		if (!next_cmd)
		{
			ft_dprintf(2, "syntax error near unexpected token `newline'\n");
			g_exit_code = MISUSE_OF_BUILTINS;
			return (0);
		}
		else if (is_redirection(next_cmd) || ft_strcmp(next_cmd, "|") == 0)
		{
			ft_dprintf(2, "syntax error near unexpected token `%s'\n", next_cmd);
			g_exit_code = MISUSE_OF_BUILTINS;
			return (0);
		}
	}
	return (1);
}

int	malloc_current_cmds(t_parsed_cmd *current, char **cmds, int i)
{
    if (current->cmds == NULL)
    {
        current->cmds = malloc(sizeof(char *) * (count_arg(&cmds[i]) + 1));
        if (current->cmds == NULL)
            return (-1);
    }
    return (0);
}

t_parsed_cmd	*create_p_cmd(void)
{
	t_parsed_cmd	*new;

	new = malloc(sizeof(t_parsed_cmd));
	if (!new)
		return (NULL);
	new->cmds = NULL;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}

int create_next_cmd(t_parsed_cmd **current, char **cmds, int *i, int *index)
{
    if (!cmds[*i + 1] || is_redirection(cmds[*i + 1])
        || ft_strcmp(cmds[*i + 1], "|") == 0)
    {
        syntax_error(cmds[*i], cmds[*i + 1]);
        return (-1);
    }
    (*current)->cmds[*index] = NULL;
    *index = 0;
    (*current)->next = create_p_cmd();
    if (!(*current)->next)
    {
        return (-1);
    }
    *current = (*current)->next;
    return (0);
}

int create_redirection(t_redirection **redir, char **cmds, int *i, char **envp)
{
    t_redirection *tmp;
	t_redirection *last;

    if (!cmds[*i + 1] || is_redirection(cmds[*i + 1]) || ft_strcmp(cmds[*i + 1], "|") == 0)
    {
        syntax_error(cmds[*i], cmds[*i + 1]);
        return (-1);
    }
    tmp = malloc(sizeof(t_redirection));
    if (!tmp)
        return (-1);
    tmp->op = handle_token(cmds[*i], envp, 1);
    tmp->fd_name = handle_token(cmds[*i + 1], envp, 1);
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

t_parsed_cmd	*parser(char **cmds, char **envp)
{
	t_parsed_cmd	*p_cmds;
	t_parsed_cmd	*current;
	int				i;	
	int				index;

	i = 0;
	index = 0;
	p_cmds = create_p_cmd();
	if (!p_cmds)
		return (NULL);
	current = p_cmds;
	while (cmds[i])
	{
		if (malloc_current_cmds(current, cmds, i) == -1)
            return (NULL);
		if (is_redirection(cmds[i]))
		{
			if (create_redirection(&(current->redir),cmds, &i, envp) == -1)
			{
				free_p_table(p_cmds, 1);
				return (NULL);
			}
		}
		else if (ft_strcmp(cmds[i], "|") == 0)
		{
			if (create_next_cmd(&current, cmds, &i, &index) == -1)
			{
				free_p_table(p_cmds, 1);
                return (NULL);
			}
		}
		else
		{
			current->cmds[index++] = handle_token(cmds[i], envp, 1); 
			if (!current->cmds[index - 1])
			{
				free_p_table(p_cmds, 1);
				return (NULL);
			}
		}
		i++;
	}
	current->cmds[index] = NULL;
	return (p_cmds);
}
