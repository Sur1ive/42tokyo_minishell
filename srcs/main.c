/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/10/12 17:52:48 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_line(int mode)
{
	static int	line_count = 0;

	if (mode == CL_READ)
		return (line_count);
	if (mode == CL_PLUS)
		return (line_count++);
	return (-1);
}

int	main(void)
{
	char		*input;
	char		**envp;
	t_cmd_table	*cmds;

	mod_sigquit_key(S_DISABLE);
	set_signal(S_ENABLE);
	init_envp(&envp);
	input = readline("$ ");
	while (input != NULL)
	{
		count_line(CL_PLUS);
		rl_already_prompted = 0;
		free(input);
		if (ft_strlen(rl_line_buffer) != 0)
			add_history(rl_line_buffer);
		cmds = parseline(rl_line_buffer, envp);
		executor(cmds, &envp);
		freecmd(cmds);
		input = readline("$ ");
	}
	free2(envp);
	shell_exit(set_exit_code(0, EC_RDONLY));
}
