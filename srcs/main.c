/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/08/03 18:36:25 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*input;
	char	**args;
	char	**envp;

	init_envp(&envp);
	set_signal();
	if (argc > 1)
	{
		exec_file(&argv[1], &envp);
		free2(envp);
		return (0);
	}
	input = readline("$ ");
	while (input != NULL)
	{
		free(input);
		add_history(rl_line_buffer);
		args = parseline(rl_line_buffer);
		exec(args, &envp);
		free2(args);
		input = readline("$ ");
	}
	free2(envp);
	return (0);
}
