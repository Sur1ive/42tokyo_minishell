/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/09/16 19:50:21 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table	*parseline_for_test(char *line);
void		freecmd_for_test(t_cmd_table *cmd);

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
		add_history(rl_line_buffer);
		cmds = parseline_for_test(rl_line_buffer);
		executor(cmds, &envp);
		freecmd_for_test(cmds);
		input = readline("$ ");
	}
	free2(envp);
	return (0);
}
