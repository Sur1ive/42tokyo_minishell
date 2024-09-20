/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:42:46 by yxu               #+#    #+#             */
/*   Updated: 2024/09/20 17:08:00 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_is_valid(char *s)
{
	int		i;

	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (s[0] != '-' && s[0] != '+' && (s[0] < '0' || s[0] > '9'))
		return (0);
	if ((s[0] == '-' || s[0] == '+') && !s[1])
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	if (args[1] == NULL)
		return (-256);
	else if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_code = GENERAL_ERR;
	}
	else
	{
		if (str_is_valid(args[1]))
			g_exit_code = ft_atoi(args[1]) % 256;
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			g_exit_code = MISUSE_OF_BUILTINS;
		}
	}
	printf("exit\n");
	return (g_exit_code * -1);
}
