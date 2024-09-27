/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 03:54:38 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/28 05:13:03 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static char	**extract_word(char **cmd, char **line, int *i, t_flags *flag)
{
	size_t	len;
	char	*word;

	len = *line - flag->start;
	word = malloc(len + 1);
	if (!word)
	{
		free2(cmd);
		return (NULL);
	}
	ft_strlcpy(word, flag->start, len + 1);
	cmd[*i] = word;
	*i += 1;
	flag->in_word = false;
	return (cmd);
}

static char	**split_op(char **cmd, char **line, int *i, t_flags *flag)
{
	if (flag->in_word && flag->start != *line)
	{
		cmd = extract_word(cmd, line, i, flag);
		if (!cmd)
			return (NULL);
	}
	if (ft_strncmp(*line, "<<", 2) == 0 || ft_strncmp(*line, ">>", 2) == 0)
	{
		cmd[*i] = ft_strndup(*line, 2);
		*line += 1;
	}
	else
		cmd[*i] = ft_strndup(*line, 1);
	if (!cmd[*i])
	{
		free2(cmd);
		return (NULL);
	}
	*i += 1;
	flag->in_word = false;
	return (cmd);
}

static void	start_quote(char **line, t_flags *flag)
{
	flag->in_quote = true;
	flag->quote_char = **line;
	if (*(*line - 1) == ' ' || *(*line - 1) == '\t' || *(*line - 1) == '|'
		|| *(*line - 1) == '<' || *(*line - 1) == '>')
	{
		flag->start = *line;
		flag->in_word = true;
	}
}

static char	**split_command(char **cmd, char **line, int *i, t_flags *flag)
{
	while (**line != '\0')
	{
		if (!flag->in_quote && (**line == '\'' || **line == '"'))
			start_quote(line, flag);
		else if (flag->in_quote && **line == flag->quote_char)
			flag->in_quote = false;
		else if (!flag->in_quote && (**line == ' ' || **line == '\t')
			&& flag->in_word)
			cmd = extract_word(cmd, line, i, flag);
		else if (!flag->in_quote
			&& (**line == '|' || **line == '>' || **line == '<'))
			cmd = split_op(cmd, line, i, flag);
		else if (!flag->in_quote && !flag->in_word
			&& (**line != ' ' && **line != '\t'))
		{
			flag->start = *line;
			flag->in_word = true;
		}
		if (!cmd)
			return (NULL);
		*line += 1;
	}
	return (cmd);
}

char	**lexer(char *line, char **command)
{
	int		wc;
	int		i;
	t_flags	flag;

	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '\n')
		return (NULL);
	wc = count_words(line);
	command = malloc((wc + 1) * sizeof(char *));
	if (!command)
		return (NULL);
	i = 0;
	flag.in_word = true;
	flag.start = line;
	flag.in_quote = false;
	flag.quote_char = '\0';
	command = split_command(command, &line, &i, &flag);
	if (command && flag.in_word && wc)
		command = extract_word(command, &line, &i, &flag);
	if (!command)
		return (NULL);
	command[i] = NULL;
	return (command);
}
