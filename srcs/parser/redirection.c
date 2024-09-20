/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:26:35 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/19 21:27:03 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table	*create_cmd_table_entry(void);
void		free_cmd_table(t_cmd_table *table);
int			is_redirection(char *token);
void		*ft_realloc(void *ptr, size_t new_size);
ssize_t		ft_getline(char **lineptr, size_t *n);

int	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;
	size_t	len;

	len = 0;
	line = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	ft_printf("heredoc> ");
	while (ft_getline(&line, &len) != -1)
	{
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		ft_printf("heredoc> ");
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	count_arg(char **command)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (command[i] && !is_redirection(command[i])
		&& ft_strcmp(command[i], "|") != 0)
	{
		count++;
		i++;
	}
	return (count);
}

void	handle_redirection(t_cmd_table *current, char **cmd, int *i, int *index)
{
	current->cmd[*index] = NULL;
	if (cmd[*i + 1])
	{
		if (strcmp(cmd[*i], ">") == 0)
			current->out = open(cmd[*i + 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (strcmp(cmd[*i], ">>") == 0)
			current->out = open(cmd[*i + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (strcmp(cmd[*i], "<") == 0)
			current->in = open(cmd[*i + 1], O_RDONLY);
		else if (strcmp(cmd[*i], "<<") == 0)
			current->in = handle_heredoc(cmd[*i + 1]);
		*i += 2;
	}
}

void	handle_pipe(t_cmd_table **current, int *cmd_index, int *i)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	(*current)->cmd[*cmd_index] = NULL;
	(*current)->out = pipefd[1];
	(*current)->next = create_cmd_table_entry();
	*current = (*current)->next;
	(*current)->in = pipefd[0];
	*cmd_index = 0;
	*i += 1;
}

t_cmd_table	*parse_command_with_redirection(char **cmd)
{
	t_cmd_table	*table;
	t_cmd_table	*current;
	int			i;
	int			cmd_index;

	table = create_cmd_table_entry();
	current = table;
	i = 0;
	cmd_index = 0;
	while (cmd[i])
	{
		if (current->cmd == NULL)
			current->cmd = malloc(sizeof(char *) * (count_arg(&cmd[i]) + 1));
		if (is_redirection(cmd[i]))
			handle_redirection(current, cmd, &i, &cmd_index);
		else if (ft_strcmp(cmd[i], "|") == 0)
			handle_pipe(&current, &cmd_index, &i);
		else
			current->cmd[cmd_index++] = ft_strdup(cmd[i++]);
	}
	if (i != 0)
		current->cmd[cmd_index] = NULL;
	else
		current->cmd = ft_calloc(1, 1);
	return (table);
}
