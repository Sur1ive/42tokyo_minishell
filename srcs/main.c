/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/10/02 18:03:12 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*input;
	char		**envp;
	t_cmd_table	*cmds;

	mod_sigquit_key(S_DISABLE);
	set_signal(S_ENABLE);
	init_envp(&envp);
	input = readline("$ ");
	rl_already_prompted = 0;
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
	shell_exit(0);
}
