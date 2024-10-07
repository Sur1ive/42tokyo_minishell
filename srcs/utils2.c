/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:59:20 by yxu               #+#    #+#             */
/*   Updated: 2024/10/07 20:54:32 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	freecmd(t_cmd_table *cmd)
{
	t_cmd_table	*next;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->in != STDIN_FILENO)
			close(cmd->in);
		if (cmd->out != STDOUT_FILENO)
			close(cmd->out);
		free2(cmd->cmd);
		free(cmd);
		cmd = next;
	}
	create_pipe(NULL, PIPECOUNTRESET);
}

char	**ft_strdup2(char **arr)
{
	char	**arr_cp;
	int		i;

	if (arr == NULL)
		return (NULL);
	arr_cp = (char **)malloc(sizeof(char *) * (ft_count(arr) + 1));
	if (arr_cp == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		arr_cp[i] = ft_strdup(arr[i]);
		if (arr_cp[i] == NULL)
		{
			free2(arr_cp);
			return (NULL);
		}
		i++;
	}
	arr_cp[i] = NULL;
	return (arr_cp);
}

int	replace_io(int in, int out)
{
	int	result1;
	int	result2;

	result1 = 0;
	result2 = 0;
	if (in != 0)
	{
		result1 = dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != 1)
	{
		result2 = dup2(out, STDOUT_FILENO);
		close(out);
	}
	if (result1 == -1 || result2 == -1)
	{
		perror(NULL);
		errno = 0;
		return (-1);
	}
	return (0);
}
