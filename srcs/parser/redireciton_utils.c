/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redireciton_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:15:56 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/23 18:31:26 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table	*create_cmd_table_entry(void)
{
	t_cmd_table	*entry;

	entry = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!entry)
		return (NULL);
	entry->cmd = NULL;
	entry->in = 0;
	entry->out = 1;
	entry->next = NULL;
	entry->prev = NULL;
	return (entry);
}

void	free_cmd_table(t_cmd_table *table)
{
	t_cmd_table	*tmp;

	while (table)
	{
		tmp = table;
		table = table->next;
		free(tmp);
	}
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
