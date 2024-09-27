/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:39:32 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/28 05:14:01 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static char	*handle_token(char *cmd, char **envp, bool	flag, bool *env_flag);

static char	*extract_var_name(char **line)
{
	char	*var_start;

	var_start = *line;
	while (**line && (ft_isalnum(**line) || **line == '_'))
		(*line)++;
	return (ft_strndup(var_start, *line - var_start));
}

static char	*process_variable(char **line, char **envp, bool *env_flag)
{
	char	*var_name;
	char	*var_value;

	(*line)++;
	if (!**line || ((!ft_isalnum(**line) && **line != '_') && **line != '?'))
		return (ft_strdup("$"));
	if (**line == '?')
	{
		(*line)++;
		return (ft_itoa(g_exit_code));
	}
	var_name = extract_var_name(line);
	if (var_name)
	{
		var_value = ft_getenv(envp, var_name);
		free(var_name);
		if (var_value)
			return (ft_strdup(var_value));
		else
			*env_flag = true;
		return (NULL);
	}
	return (ft_strdup(""));
}

static char	*handle_quotes(char **cmd, char **envp)
{
	char	quote;
	char	*end;
	char	*tmp;
	char	*sub_str;

	quote = **cmd;
	end = ft_strchr(*cmd + 1, quote);
	if (!end)
		return (NULL);
	if (quote == '\'')
		tmp = ft_strndup(*cmd + 1, end - *cmd - 1);
	else
	{
		sub_str = ft_strndup(*cmd + 1, end - *cmd - 1);
		tmp = handle_token(sub_str, envp, 0, NULL);
		free(sub_str);
	}
	*cmd = end + 1;
	return (tmp);
}

static char	*handle_token(char *cmd, char **envp, bool	flag, bool *env_flag)
{
	char	*result;
	char	*tmp;

	if (!cmd)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*cmd)
	{
		if (flag && (*cmd == '"' || *cmd == '\''))
			tmp = handle_quotes(&cmd, envp);
		else if (*cmd == '$')
			tmp = process_variable(&cmd, envp, env_flag);
		else
		{
			tmp = ft_strndup(cmd, 1);
			cmd++;
		}
		if (!tmp)
		{
			free(result);
			return (NULL);
		}
		result = ft_strjoin_free(result, tmp);
		if (!result)
			return (NULL);
	}
	return (result);
}

t_cmd_table	*expand_envs(t_cmd_table	*table, char **envp)
{
	int				i;
	int				index;
	bool			env_flag;
	char			*tmp;
	t_cmd_table		*current;
	t_redirection	*r_current;

	env_flag = false;
	current = table;
	while (current)
	{
		r_current = current->redir;
		while (r_current)
		{
			tmp = r_current->fd_name;
			r_current->fd_name = handle_token(r_current->fd_name, envp, 1, &env_flag);
			if (!r_current->fd_name)
			{
				if (env_flag)
				{
					ft_dprintf(2, " ambiguous redirect\n");
					g_exit_code = MISUSE_OF_BUILTINS;
				}
				free(tmp);
				free_table(table);
				return (NULL);
			}
			free(tmp);
			r_current = r_current->next;
		}
		i = 0;
		index = 0;
		while (current->cmd[i])
		{
			tmp = current->cmd[i];
			current->cmd[index] = handle_token(current->cmd[i], envp, 1, &env_flag);
			if (!current->cmd[i] && !env_flag)
			{
				free(tmp);
				free_table(table);
				return (NULL);
			}
			if (env_flag)
			{
				index--;
				env_flag = false;
			}
			free(tmp);
			i++;
			index++;
		}
		current->cmd[index] = NULL;
		current = current->next;
	}
	return (table);
}
