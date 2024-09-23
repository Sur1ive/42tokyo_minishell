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

char		*ft_strjoin_free(char const *s1, char const *s2);
static char	*handle_token(char *cmd, char **envp, bool flag);

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
		if (var_value)
		{
			free(var_name);
			var_value = ft_strdup(var_value);
			return (var_value);
		}
		free(var_name);
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
	{
		*cmd = *cmd + 1;
		return (ft_strdup(""));
	}
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

static char	*handle_token(char *cmd, char **envp, bool	flag)
{
	char	*result;
	char	*tmp;

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

char	**handle_env(char **cmd, char **envp)
{
	int		i;
	char	*s_ptr;

	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		s_ptr = cmd[i];
		cmd[i] = handle_token(cmd[i], envp, 1);
		if (cmd[i] == NULL)
		{
			free2(cmd);
			return (NULL);
		}
		free(s_ptr);
		i++;
	}
	return (cmd);
}
