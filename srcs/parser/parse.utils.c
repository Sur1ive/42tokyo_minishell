/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:28:40 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/30 19:15:39 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	is_redirection(char *token)
{
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

int	count_arg(char **command)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (command[i] && ft_strcmp(command[i], "|") != 0)
	{
		if (command[i + 1] && is_redirection(command[i]))
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

static void	count_special_char(char **line, int *wc, bool *in_word)
{
	(*wc)++;
	if ((**line == '>' && *(*line + 1) == '>')
		|| (**line == '<' && *(*line + 1) == '<'))
		(*line)++;
	*in_word = false;
}

static void	count_q_word(char **line, char *quote_char, int *wc, bool *in_word)
{
	*quote_char = **line;
	if (!(*in_word))
	{
		(*wc)++;
		*in_word = true;
	}
}

int	count_words(char *line)
{
	int		wc;
	bool	in_word;
	char	quote_char;

	wc = 0;
	in_word = false;
	quote_char = '\0';
	while (*line)
	{
		if (quote_char && *line == quote_char)
			quote_char = '\0';
		else if (!quote_char && (*line == '\'' || *line == '"'))
			count_q_word(&line, &quote_char, &wc, &in_word);
		else if (!quote_char && (*line == '|' || *line == '<' || *line == '>'))
			count_special_char(&line, &wc, &in_word);
		else if (!quote_char && (*line == ' ' || *line == '	'))
			in_word = false;
		else if (!in_word)
		{
			wc++;
			in_word = true;
		}
		line++;
	}
	return (wc);
}
