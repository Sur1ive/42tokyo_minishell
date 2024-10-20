/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:07:41 by yxu               #+#    #+#             */
/*   Updated: 2024/10/20 15:02:33 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_env_item(char *arg)
{
	char	**splited;
	int		equal_i;

	equal_i = ft_strchr(arg, '=') - arg;
	splited = (char **)malloc(sizeof(char *) * 3);
	if (!splited)
		return (NULL);
	splited[0] = (char *)malloc(sizeof(char) * (equal_i + 1));
	splited[1] = (char *)
		malloc(sizeof(char) * (ft_strlen(arg) - equal_i));
	splited[2] = NULL;
	if (!splited[0] || !splited[1])
	{
		free2(splited);
		return (NULL);
	}
	ft_strlcpy(splited[0], arg, equal_i + 1);
	ft_strlcpy(splited[1], arg + equal_i + 1, ft_strlen(arg) - equal_i);
	return (splited);
}

static int	is_valid_env(char *arg)
{
	int	i;

	if (ft_strlen(arg) == 0)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	handle_env_error(char *arg)
{
	if (is_valid_env(arg) && ft_strchr(arg, '=') == NULL)
		return (0);
	ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", arg);
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
		if (is_valid_env(args[i]) && ft_strchr(args[i], '='))
		{
			splited = split_env_item(args[i]);
			if (splited == NULL || ft_setenv(envpp, splited[0], splited[1]))
				ft_dprintf(2, "minishell: export: %s\n", strerror(errno));
			errno = 0;
			free2(splited);
		}
		else if (handle_env_error(args[i]) == 1)
			fail_flag = 1;
		i++;
	}
	return (fail_flag);
}
