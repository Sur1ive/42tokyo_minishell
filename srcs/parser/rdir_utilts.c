/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_utilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:15:56 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/30 19:13:09 by nakagawashi      ###   ########.fr       */
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

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

int	read_and_process_line(int pipefd, char *delimiter, char **envp)
{
	char	*line;
	char	*expanded_line;

	line = readline("> ");
	if (!line)
		return (-1);
	expanded_line = handle_token(line, envp, 1, NULL);
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

int	set_heredoc(char *delimiter, char **envp)
{
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		status = read_and_process_line(pipefd[1], delimiter, envp);
		if (status <= 0)
			break ;
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
