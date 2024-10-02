/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:38:38 by yxu               #+#    #+#             */
/*   Updated: 2024/10/02 13:48:23 by yxu              ###   ########.fr       */
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
	if (mode == SQ_DISABLE)
		new_termios.c_cc[VQUIT] = 0;
	else if (mode == SQ_RESTORE)
		new_termios.c_cc[VQUIT] = origin_mode;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) < 0)
		perror(NULL);
}

int	init_envp(char ***envpp)
{
	*envpp = ft_strdup2(__environ);
	if (*envpp == NULL)
	{
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
		shell_exit(GENERAL_ERR);
	}
	return (0);
}

static void	deal_signal(int signum)
{
	if (signum == SIGINT)
	{
		set_exit_code(MANUAL_TERM, 0);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_already_prompted = 1;
	}
}

void	set_signal(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		shell_exit(GENERAL_ERR);
	sa.sa_handler = deal_signal;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		shell_exit(GENERAL_ERR);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		shell_exit(GENERAL_ERR);
}
