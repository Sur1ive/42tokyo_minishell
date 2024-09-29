/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/09/29 18:30:45 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(void)
{
	char		*input;
	char		**envp;
	t_cmd_table	*cmds;

	init_envp(&envp);
	set_signal();
	input = readline("$ ");
	while (input != NULL)
	{
		free(input);
		if (ft_strlen(rl_line_buffer) != 0)
			add_history(rl_line_buffer);
		cmds = parseline(rl_line_buffer, envp);
		executor(cmds, &envp);
		freecmd(cmds);
		input = readline("$ ");
		rl_already_prompted = 0;
	}
	free2(envp);
	return (0);
}
