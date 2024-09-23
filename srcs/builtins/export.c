/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:07:41 by yxu               #+#    #+#             */
/*   Updated: 2024/09/23 13:57:57 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_env_item(char *arg)
{
	char	**splited;
	int		equal_index;

	equal_index = ft_strchr(arg, '=') - arg;
	splited = (char **)malloc(sizeof(char *) * 3);
	if (!splited)
		return (NULL);
	splited[2] = NULL;
	splited[0] = (char *)malloc(sizeof(char) * (equal_index + 1));
	splited[1] = (char *)malloc(sizeof(char) * (ft_strlen(arg) - equal_index));
	if (!splited[0] || !splited[1])
	{
		free2(splited);
		return (NULL);
	}
	ft_strlcpy(splited[0], arg, equal_index + 1);
	ft_strlcpy(splited[1], arg + equal_index + 1, ft_strlen(arg) - equal_index);
	return (splited);
}

static int	is_valid_env(char *arg)
{
	if (ft_strlen(arg) < 2)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	if (ft_strchr(arg, '=') == NULL)
		return (0);
	return (1);
}

int	export(char **args, char ***envpp)
{
	char	**splited;
	int		fail_flag;
	int		i;

	i = 1;
	fail_flag = 0;
	while (args[i])
	{
		if (is_valid_env(args[i]))
		{
			splited = split_env_item(args[i]);
			if (splited == NULL || ft_setenv(envpp, splited[0], splited[1]))
				ft_dprintf(2, "minishell: export: %s\n", strerror(errno));
			free2(splited);
		}
		else
		{
			ft_dprintf
				(2, "minishell: export: %s: not a valid identifier\n", args[i]);
			fail_flag = 1;
		}
		i++;
	}
	return (fail_flag);
}
