/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:37 by yxu               #+#    #+#             */
/*   Updated: 2024/09/26 13:54:30 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

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

t_cmd_table	*parseline(char *line, char **envp)
{
	char			**command;
	t_parsed_cmd 	*cmds;
	t_cmd_table		*cmd_table;

	command = NULL;
	cmds = NULL;
	command = lexer(line, command);
	if (!command)
		return (NULL);
	cmds = parser(command, envp);
	free2(command);
	if (!cmds)
		return (NULL);
	// for (t_parsed_cmd *tmp = cmds; tmp; tmp = tmp->next)
	// {
	// 	for (int i=0; tmp->cmds[i]; i++)
	// 		printf("[%d]:%s\n",i,tmp->cmds[i]);
	// }
	cmd_table = exec_preparator(cmds);
	free_p_table(cmds, 0);
	// for (t_cmd_table *tmp = cmd_table; tmp; tmp = tmp->next)
	// {
	// 	for (int i=0; tmp->cmd[i]; i++)
	// 		printf("[%d]:%s\n",i,tmp->cmd[i]);
	// }
	return (cmd_table);
}
