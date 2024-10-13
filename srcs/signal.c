/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:38:38 by yxu               #+#    #+#             */
/*   Updated: 2024/10/13 21:47:31 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		count_line(CL_PLUS);
	}
}

static void	deal_signal_while_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		set_exit_code(MANUAL_TERM, 0);
		rl_done = 1;
	}
}

/*
	rl_done is only checked in the event loop.
	When you give it a null event hook function, it checks the rl_done and exits.
*/
static int	event(void)
{
	return (0);
}

void	set_signal(int mode)
{
	struct sigaction	sa;

	rl_event_hook = event;
	if (sigemptyset(&sa.sa_mask) == -1)
		perror(NULL);
	if (mode == S_DISABLE)
		sa.sa_handler = SIG_IGN;
	else if (mode == S_HEREDOC)
		sa.sa_handler = deal_signal_while_heredoc;
	else
		sa.sa_handler = deal_signal;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror(NULL);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror(NULL);
}
