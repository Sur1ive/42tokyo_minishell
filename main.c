/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/07/29 10:13:53 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parseline(char *line)
{
	(void)line;
	// printf("line: | %s |\n", line);
	return (0);
}

int	main(void)
{
	char	*line;

	while (line != NULL)
	{
		line = readline("$ ");
		free(line);
		add_history(rl_line_buffer);
		parseline(rl_line_buffer);
		rl_replace_line("aaaaaaaaaa\n", 1);
		rl_redisplay();
	}
	return (0);
}
