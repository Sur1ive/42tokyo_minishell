/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:38:38 by yxu               #+#    #+#             */
/*   Updated: 2024/08/03 18:40:00 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_envp(char ***envpp)
{
	int		flag;
	char	workdir[PATH_MAX + 1];

	*envpp = NULL;
	ft_memset(workdir, 0, PATH_MAX + 1);
	flag = 0;
	flag += ft_setenv(envpp, "PWD", getcwd(workdir, PATH_MAX));
	flag += ft_setenv(envpp, "PATH", getenv("PATH"));
	if (flag < 0)
	{
		printf("minishell: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

static void	deal_signal(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		return ;
}

void	set_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = deal_signal;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("minishell: %s\n", strerror(errno));
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		printf("minishell: %s\n", strerror(errno));
}
