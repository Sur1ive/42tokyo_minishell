/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:38:38 by yxu               #+#    #+#             */
/*   Updated: 2024/10/01 12:04:22 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_strdup2(char **arr)
{
	char	**arr_cp;
	int		i;

	if (arr == NULL)
		return (NULL);
	arr_cp = (char **)malloc(sizeof(char *) * (ft_count(arr) + 1));
	if (arr_cp == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		arr_cp[i] = ft_strdup(arr[i]);
		if (arr_cp[i] == NULL)
		{
			free2(arr_cp);
			return (NULL);
		}
		i++;
	}
	arr_cp[i] = NULL;
	return (arr_cp);
}

int	init_envp(char ***envpp)
{
	*envpp = ft_strdup2(__environ);
	if (*envpp == NULL)
	{
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
		exit(GENERAL_ERR);
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
	{
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
		errno = 0;
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
		errno = 0;
	}
}
