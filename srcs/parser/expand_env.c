/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:39:32 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/10/07 19:41:35 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

char	*handle_token(char *cmd, char **envp, bool	flag, bool *env_flag);

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*str;
	char	*start;
	char	*s1_start;
	char	*s2_start;

	if (s1 == NULL)
		return (NULL);
	str = (char *)malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	start = str;
	s1_start = (char *)s1;
	s2_start = (char *)s2;
	if (str == NULL)
	{
		free(s1_start);
		free(s2_start);
		return (NULL);
	}
	while (*s1 != '\0')
		*str++ = *s1++;
	while (s2 && *s2 != '\0')
		*str++ = *s2++;
	*str = '\0';
	free(s1_start);
	free(s2_start);
	return (start);
}

static char	*extract_var_name(char **line)
{
	char	*var_start;

	var_start = *line;
	while (**line && (ft_isalnum(**line) || **line == '_'))
		(*line)++;
	if (var_start == *line)
		return (NULL);
	return (ft_strndup(var_start, *line - var_start));
}

char	*process_variable(char **line, char **envp, bool *env_flag)
{
	char	*var_name;
	char	*var_value;

	(*line)++;
	if (!**line || ((!ft_isalnum(**line) && **line != '_') && **line != '?'))
		return (ft_strdup("$"));
	if (**line == '?')
	{
		(*line)++;
		return (ft_itoa(set_exit_code(0, EC_RDONLY)));
	}
	var_name = extract_var_name(line);
	if (var_name)
	{
		var_value = ft_getenv(envp, var_name);
		free(var_name);
		if (var_value)
		{
			*env_flag = false;
			return (ft_strdup(var_value));
		}
		else
			*env_flag = true;
	}
	return (NULL);
}

static char	*handle_quotes(char **cmd, char **envp, bool *env_flag)
{
	char	quote;
	char	*end;
	char	*tmp;
	char	*sub_str;

	quote = **cmd;
	end = ft_strchr(*cmd + 1, quote);
	if (!end)
	{
		ft_dprintf(2, "quote error\n");
		return (NULL);
	}
	if (quote == '\'')
		tmp = ft_strndup(*cmd + 1, end - *cmd - 1);
	else
	{
		sub_str = ft_strndup(*cmd + 1, end - *cmd - 1);
		tmp = handle_token(sub_str, envp, 0, env_flag);
		free(sub_str);
	}
	*cmd = end + 1;
	return (tmp);
}

char	*handle_token(char *cmd, char **envp, bool	flag, bool *env_flag)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	while (*cmd && result)
	{
		if (flag && (*cmd == '"' || *cmd == '\''))
			tmp = handle_quotes(&cmd, envp, env_flag);
		else if (*cmd == '$')
			tmp = process_variable(&cmd, envp, env_flag);
		else
			tmp = ft_strndup(cmd++, 1);
		if (!tmp && !*env_flag)
		{
			free(result);
			return (NULL);
		}
		result = ft_strjoin_free(result, tmp);
	}
	if (!ft_strcmp(result, "\0") && *env_flag)
	{
		free(result);
		return (NULL);
	}
	return (result);
}
