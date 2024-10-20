/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_utilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:15:56 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/10/20 13:10:54 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

char	*get_a_line(int flag, bool *env_flag, char **envp, char *line)
{
	char	*expanded_line;
	char	*tmp;

	expanded_line = NULL;
	if (!flag && line)
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
	else if (line)
		expanded_line = ft_strdup(line);
	return (expanded_line);
}

static int	write_to_pipe(int pipefd, char **data)
{
	if (write(pipefd, *data, ft_strlen(*data)) == -1)
	{
		perror("write");
		free(*data);
		data = NULL;
		return (-1);
	}
	if (write(pipefd, "\n", 1) == -1)
	{
		perror("write");
		free(*data);
		data = NULL;
		return (-1);
	}
	return (0);
}

int	read_and_process_line(int pipefd, char *delimiter, char **envp, int flag)
{
	char	*line;
	char	*expanded_line;
	bool	env_flag;

	env_flag = false;
	set_signal(S_HEREDOC);
	set_exit_code(EXIT_SUCCESS, 0);
	line = readline("> ");
	set_signal(S_ENABLE);
	if (set_exit_code(0, EC_RDONLY) == MANUAL_TERM)
		return (MANUAL_TERM * -1);
	if (!line)
		return (dprintf(2, "minishell: warning: here-document at line %d delimited \
by end-of-file (wanted `%s')\n", count_line(CL_READ), delimiter) * 0);
	free(line);
	if (ft_strcmp(rl_line_buffer, delimiter) == 0)
		return (0);
	expanded_line = get_a_line(flag, &env_flag, envp, rl_line_buffer);
	if (!expanded_line)
		return (-1);
	if (write_to_pipe(pipefd, &expanded_line) == -1)
		return (-1);
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
	if (!delimiter || create_pipe(pipefd, CREATE) == -1)
		return (-1);
	while (1)
	{
		status = read_and_process_line(pipefd[1], *delimiter, envp, flag);
		if (status == MANUAL_TERM * -1)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			return (MANUAL_TERM * -1);
		}
		if (status <= 0)
			break ;
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
