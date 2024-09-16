/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:52:06 by yxu               #+#    #+#             */
/*   Updated: 2024/09/08 18:20:08 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *arg, char opt)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i++] != opt)
			return (0);
	}
	if (i == 1)
		return (0);
	return (1);
}

int	echo(char **args)
{
	int	i;
	int	opt_n;

	opt_n = 0;
	i = 1;
	while (args[i])
	{
		if (is_option(args[i], 'n'))
		{
			opt_n = 1;
			i++;
		}
		else
			break ;
	}
	if (args[i])
		printf("%s", args[i++]);
	while (args[i])
		printf(" %s", args[i++]);
	if (opt_n == 0)
		printf("\n");
	return (0);
}
