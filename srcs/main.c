/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/07/30 11:36:05 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**commandline;

	if (argc > 1)
	{
		(void)argv;
		// exec
		return (0);
	}
	input = readline("$ ");
	while (input != NULL)
	{
		free(input);
		add_history(rl_line_buffer);
		commandline = parseline(rl_line_buffer);
		exec(commandline, envp);
		input = readline("$ ");
	}
	return (0);
}
