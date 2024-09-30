/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:07:45 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/30 19:34:26 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	redir_env(t_redirection *r_current, char **envp,
	t_cmd_table *table, bool *env_flag)
{
	char	*tmp;

	while (r_current)
	{
		tmp = r_current->fd_name;
		if (ft_strcmp(r_current->op, "<<") != 0)
			r_current->fd_name = handle_token(tmp, envp, 1, env_flag);
		else
			r_current->fd_name = ft_strdup(r_current->fd_name);
		if (!r_current->fd_name)
		{
			if (*env_flag)
			{
				ft_dprintf(2, "minishell: %s: ambiguous redirect\n", tmp);
				g_exit_code = MISUSE_OF_BUILTINS;
			}
			free(tmp);
			free_table(table);
			return (-1);
		}
		free(tmp);
		r_current = r_current->next;
	}
	return (0);
}

int	cmd_env(char **cmd, char **envp, t_cmd_table *table, bool *env_flag)
{
	int		i;
	int		index;
	char	*tmp;

	i = 0;
	index = 0;
	while (cmd[i])
	{
		tmp = cmd[i];
		cmd[index] = handle_token(tmp, envp, 1, env_flag);
		if (!cmd[index] && !(*env_flag))
		{
			free(tmp);
			free_table(table);
			return (-1);
		}
		free(tmp);
		if (*env_flag)
			*env_flag = false;
		else
			index++;
		i++;
	}
	cmd[index] = NULL;
	return (0);
}

t_cmd_table	*expand_envs(t_cmd_table *table, char **envp)
{
	t_cmd_table		*current;
	t_redirection	*r_current;
	bool			env_flag;

	env_flag = false;
	current = table;
	while (current)
	{
		r_current = current->redir;
		if (redir_env(r_current, envp, table, &env_flag) == -1)
			return (NULL);
		if (cmd_env(current->cmd, envp, table, &env_flag) == -1)
			return (NULL);
		current = current->next;
	}
	return (table);
}
