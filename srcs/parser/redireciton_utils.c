/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redireciton_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:15:56 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/26 11:49:02 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

t_cmd_table	*create_cmd_table_entry(t_parsed_cmd *p_cmds)
{
	t_cmd_table	*entry;

	entry = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!entry)
		return (NULL);
	if (p_cmds)
		entry->cmd = p_cmds->cmds;
	else
		entry->cmd = NULL;
	entry->in = STDIN_FILENO;
	entry->out = STDOUT_FILENO;
	entry->next = NULL;
	entry->prev = NULL;
	return (entry);
}

int	is_redirection(char *token)
{
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		return (1);
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

ssize_t	ft_getline(char **lineptr, size_t *n)
{
	char	*buffer;
	size_t	total_len;

	total_len = 0;
	if (*lineptr == NULL)
	{
		*n = BUFFER_SIZE;
		*lineptr = malloc(BUFFER_SIZE);
	}
	buffer = *lineptr;
	while (read(STDIN_FILENO, &buffer[total_len], 1) > 0)
	{
		if (total_len >= *n - 1)
		{
			*n *= 2;
			*lineptr = ft_realloc(*lineptr, *n);
			buffer = *lineptr;
		}
		if (buffer[total_len] == '\n')
			break ;
	}
	buffer[total_len] = '\0';
	if (total_len > 0)
		return (total_len);
	return (-1);
}

