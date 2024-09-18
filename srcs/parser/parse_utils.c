/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 03:54:38 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/19 00:00:30 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char const *s1, char const *s2);
int		count_words(const char *line);
int		is_redirection(char *token);

static char	*extract_word(char **command, char *start, char *end)
{
	size_t	len;
	char	*word;

	len = end - start;
	word = malloc(len + 1);
	if (!word)
	{
		free2(command);
		return (NULL);
	}
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static char	**handle_quote(char **cmd, char **line, int *i, t_flags *flag)
{
	char	*end;
	char	quote;
	char	*q_str;

	quote = **line;
	end = ft_strchr(*line + 1, quote);
	if (!end)
	{
		free2(cmd);
		return (NULL);
	}
	q_str = ft_strndup(*line, end - *line + 1);
	if (!q_str)
		return (NULL);
	if (*(*line - 1) != ' ' && *(*line - 1) != '\t')
		cmd[*i] = ft_strjoin_free(extract_word(cmd, flag->start, *line), q_str);
	else
		cmd[*i] = q_str;
	if (*(end + 1) == ' ' || *(end + 1) == '\t' || *(end + 1) == '\0')
		flag->in_word = false;
	else
	{
		flag->in_word = true;
		flag->new_word_start = false;
	}
	flag->start = end + 1;
	*line = end;
	return (cmd);
}

static char	**process_word(char **cmd, char **line, int *i, t_flags *flag)
{
	char	*tmp;

	if (!flag->new_word_start)
	{
		tmp = extract_word(cmd, flag->start, *line);
		cmd[*i - 1] = ft_strjoin_free(cmd[*i - 1], tmp);
	}
	else
	{
		cmd[*i] = extract_word(cmd, flag->start, *line);
		*i += 1;
	}
	if (!cmd[*i - 1])
	{
		free2(cmd);
		return (NULL);
	}
	flag->in_word = false;
	flag->new_word_start = true;
	return (cmd);
}

static char	**handle_special_char(char **cmd, char **line, int *i, t_flags *flag)
{
	if (flag->in_word && flag->start != *line)
	{
		cmd = process_word(cmd, line, i, flag);
		if (!cmd)
			return (NULL);
	}
	if ((**line == '<' && *(*line + 1) == '<') || (**line == '>' && *(*line + 1) == '>'))
	{
		cmd[*i] = ft_strndup(*line, 2);
		if (!cmd[*i])
		{
			free2(cmd);
			return (NULL);
		}
		*line += 1;
	}
	else
	{
		cmd[*i] = ft_strndup(*line, 1);
		if (!cmd[*i])
		{
			free2(cmd);
			return (NULL);
		}
	}
	*i += 1;
	flag->in_word = false;
	flag->new_word_start = true;
	return (cmd);
}

static char	**split_command_sub(char **cmd, char **line, int *i, t_flags *flag)
{
	while (**line != '\0')
	{
		if (flag->in_word && (**line == ' ' || **line == '\t'))
			cmd = process_word(cmd, line, i, flag);
		else if (**line == '\'' || **line == '"')
		{
			cmd = handle_quote(cmd, line, i, flag);
			if (!cmd)
				errno = EINVAL;
			*i += 1;
		}
		else if (**line == '|' || **line == '>' || **line == '<' )
		{
			cmd = handle_special_char(cmd, line, i, flag);
			if (!cmd)
				return (NULL);
		}
		else if (**line != ' ' && **line != '\t' && !(flag->in_word))
		{
			flag->start = *line;
			flag->in_word = true;
		}
		if (!cmd || !cmd[*i - 1])
		{
			if (cmd)
				free2(cmd);
			return (NULL);
		}
		*line += 1;
	}
	return (cmd);
}

char	**split_command(char *line, char **command)
{
	int		wc;
	int		i;
	t_flags	flag;

	wc = count_words(line);
	printf("count:%d\n",wc);
	command = malloc((wc + 1) * sizeof(char *));
	if (!command)
		return (NULL);
	while (*line == ' ' || *line == '\t')
		line++;
	i = 0;
	flag.in_word = true;
	flag.start = line;
	flag.new_word_start = true;
	command = split_command_sub(command, &line, &i, &flag);
	if (command && flag.in_word && wc)
		command = process_word(command, &line, &i, &flag);
	if (!command)
		return (NULL);
	command[i] = NULL;
	return (command);
}
