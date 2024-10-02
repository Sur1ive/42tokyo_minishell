/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:42:46 by yxu               #+#    #+#             */
/*   Updated: 2024/10/02 13:48:36 by yxu              ###   ########.fr       */
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

int	set_exit_code(int new_exit_code, int mode)
{
	static int	exit_code = 0;

	if (mode != EC_RDONLY)
		exit_code = new_exit_code;
	return (exit_code);
}

void	shell_exit(int status)
{
	mod_sigquit_key(SQ_RESTORE);
	exit(status);
}

int	builtin_exit(char **args)
{
	if (args[1] == NULL)
		return (-256);
	else if (args[2])
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		set_exit_code(GENERAL_ERR, 0);
	}
	else if (str_is_valid(args[1]))
		set_exit_code(ft_atoi(args[1]) % 256, 0);
	else
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
			args[1]);
		set_exit_code(MISUSE_OF_BUILTINS, 0);
	}
	printf("exit\n");
	return (set_exit_code(0, EC_RDONLY) * -1);
}
