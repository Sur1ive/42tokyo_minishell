/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:39:32 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/03 01:52:44 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static char	*extract_var_name(char **line)
{
	char	*var_start;

	var_start = *line;
	while (**line && (ft_isalnum(**line) || **line == '_'))
		(*line)++;
	return (ft_strndup(var_start, *line - var_start));
}

static char	*process_variable(char **line, char **envp)
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
		{
			var_value = ft_strdup(var_value);
			return (var_value);
		}
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
		tmp = handle_token(sub_str, envp, 0);
		free(sub_str);
	}
	*cmd = end + 1;
	return (tmp);
}

char	*handle_token(char *cmd, char **envp, bool	flag)
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
			tmp = process_variable(&cmd, envp);
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
	}
	return (result);
}

// t_parsed_cmd *handle_env(t_parsed_cmd *cmd, char **envp)
// {
// 	int		i;
// 	char	*s_ptr;
// 	t_redirection	*tmp;
// 	t_parsed_cmd *head;

// 	if (!cmd)
// 		return (NULL);
// 	head = cmd;
// 	while (cmd)
// 	{
// 		i = 0;
// 		while (cmd->cmds[i])
// 		{
// 			s_ptr = cmd->cmds[i];
// 			cmd->cmds[i] = handle_token(cmd->cmds[i], envp, 1);
// 			if (cmd->cmds[i] == NULL)
// 			{
// 				return (NULL);
// 			}
// 			free(s_ptr);
// 			i++;
// 		}
// 		tmp = cmd->redir;
// 		while (tmp)
// 		{
// 			s_ptr = tmp->fd_name;
// 			tmp->fd_name = handle_token(tmp->fd_name, envp, 1);
// 			if (tmp->fd_name == NULL)
// 				return (NULL);
// 			free(s_ptr);
// 			tmp = tmp->next;
// 		}
// 		cmd = cmd->next;
// 	}
// 	return (head);
// }
