/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/07/29 15:37:05 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free2(char **p)
{
	int	i;

	if (p == NULL)
		return ;
	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

char	**parseline(char *line)
{
	char	**command;

	command = ft_split(line, ' ');
	return (command);
}

int	main(void)
{
	char	*line;
	char	**command;

	while (line != NULL)
	{
		line = readline("$ ");
		free(line);
		add_history(rl_line_buffer);
		command = parseline(rl_line_buffer);
		free2(command);
	}
	return (0);
}
