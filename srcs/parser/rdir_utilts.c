/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_utilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:15:56 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/10/06 12:05:36 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

t_cmd_table	*create_cmd_table_entry(void)
{
	t_cmd_table	*entry;

	entry = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!entry)
		return (NULL);
	entry->cmd = NULL;
	entry->redir = NULL;
	entry->in = STDIN_FILENO;
	entry->out = STDOUT_FILENO;
	entry->next = NULL;
	entry->prev = NULL;
	return (entry);
}

int	handle_pipe(t_cmd_table **current)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if ((*current)->out == STDOUT_FILENO)
		(*current)->out = pipefd[1];
	(*current)->next->prev = *current;
	*current = (*current)->next;
	(*current)->in = pipefd[0];
	return (0);
}

char	*get_a_line(int flag, bool *env_flag, char **envp, char *line)
{
	char	*expanded_line;
	char	*tmp;

	if (!flag)
	{
		expanded_line = ft_strdup("");
		while (*line && expanded_line)
		{
			if (*line == '$')
				tmp = process_variable(&line, envp, env_flag);
			else
				tmp = ft_strndup(line++, 1);
			if (!tmp && !env_flag)
			{
				free(expanded_line);
				return (NULL);
			}
			expanded_line = ft_strjoin_free(expanded_line, tmp);
		}
	}
	else
		expanded_line = ft_strdup(line);
	return (expanded_line);
}

int	read_and_process_line(int pipefd, char *delimiter, char **envp, int flag)
{
	char	*line;
	char	*expanded_line;
	bool	env_flag;

	env_flag = false;
	line = readline("> ");
	expanded_line = get_a_line(flag, &env_flag, envp, line);
	free(line);
	if (!expanded_line)
		return (-1);
	if (ft_strcmp(expanded_line, delimiter) == 0)
	{
		free(expanded_line);
		return (0);
	}
	if (write(pipefd, expanded_line, ft_strlen(expanded_line)) == -1
		|| write(pipefd, "\n", 1) == -1)
	{
		perror("write");
		free(expanded_line);
		return (-1);
	}
	free(expanded_line);
	return (1);
}

char	*set_deli(char *delimiter, int *flag)
{
	char	*end;
	char	*result;
	char	*tmp;

	*flag = 0;
	result = ft_strdup("");
	while (*delimiter && result)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			end = ft_strchr(delimiter + 1, *delimiter);
			*flag = 1;
			tmp = ft_strndup(delimiter + 1, end - delimiter - 1);
			delimiter = end + 1;
		}
		else
			tmp = ft_strndup(delimiter++, 1);
		if (!tmp)
		{
			free(result);
			return (NULL);
		}
		result = ft_strjoin_free(result, tmp);
	}
	return (result);
}

int	set_heredoc(char **delimiter, char **envp)
{
	int		pipefd[2];
	int		status;
	int		flag;
	char	*tmp;

	tmp = *delimiter;
	*delimiter = set_deli(*delimiter, &flag);
	free(tmp);
	if (!delimiter)
		return (-1);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		status = read_and_process_line(pipefd[1], *delimiter, envp, flag);
		if (status <= 0)
			break ;
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
