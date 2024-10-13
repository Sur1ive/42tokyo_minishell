/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:51:09 by yxu               #+#    #+#             */
/*   Updated: 2024/10/13 21:37:14 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mod_sigquit_key(int mode)
{
	static cc_t		origin_mode = 255;
	struct termios	new_termios;

	if (!isatty(STDIN_FILENO))
		return ;
	if (tcgetattr(STDIN_FILENO, &new_termios) < 0)
	{
		perror(NULL);
		return ;
	}
	if (origin_mode == 255)
		origin_mode = new_termios.c_cc[VQUIT];
	if (mode == S_DISABLE)
		new_termios.c_cc[VQUIT] = 0;
	else
		new_termios.c_cc[VQUIT] = origin_mode;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) < 0)
		perror(NULL);
}

// 環境変数を初期化する。環境変数の配列envpはmallocで確保するため、
// プログラム終了時にfreeする必要がある。
static int	init_envp(char ***envpp)
{
	*envpp = ft_strdup2(__environ);
	if (*envpp == NULL)
	{
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
		shell_exit(GENERAL_ERR);
	}
	return (0);
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
