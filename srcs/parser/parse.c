/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:37 by yxu               #+#    #+#             */
/*   Updated: 2024/09/03 01:22:17 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**split_command(char *line, char **command);
char		**handle_env(char **cmd, char **envp);
t_cmd_table	*parse_command_with_redirection(char **command);

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

int	count_words(const char *line)
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
			quote_char = *line;
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

char	**parseline(char *line, char **envp)
{
	char		**command;

	command = NULL;
	command = split_command(line, command);
	if (command)
		command = handle_env(command, envp);
	if (!command)
		return (NULL);
	/*commandがNULLになった時どうする（malloc失敗時）*/
	return (command);
}
