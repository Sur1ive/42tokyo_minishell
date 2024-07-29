/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/07/29 15:54:17 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*line;
	char	**command;

	if (argc > 1)
	{
		exec(argv + 1);
		return (0);
	}
	while (line != NULL)
	{
		line = readline("$ ");
		free(line);
		add_history(rl_line_buffer);
		command = parseline(rl_line_buffer);
		exec(command);
	}
	return (0);
}
