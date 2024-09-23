/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:07:41 by yxu               #+#    #+#             */
/*   Updated: 2024/09/23 19:05:19 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_env_item(char *arg)
{
	char	**splited;
	int		equal_i;

	if (ft_strchr(arg, '=') != NULL)
		equal_i = ft_strchr(arg, '=') - arg;
	else
		equal_i = ft_strlen(arg);
	splited = (char **)malloc(sizeof(char *) * 3);
	if (!splited)
		return (NULL);
	splited[0] = (char *)malloc(sizeof(char) * (equal_i + 1));
	splited[1] = (char *)
		malloc(sizeof(char) * ((ft_strlen(arg) - equal_i) || 1));
	splited[2] = NULL;
	if (!splited[0] || !splited[1])
	{
		free2(splited);
		return (NULL);
	}
	ft_strlcpy(splited[0], arg, equal_i + 1);
	if ((size_t)equal_i != ft_strlen(arg))
		ft_strlcpy(splited[1], arg + equal_i + 1, ft_strlen(arg) - equal_i);
	else
		splited[1][0] = '\0';
	return (splited);
}

static int	is_valid_env(char *arg)
{
	if (ft_strlen(arg) == 0)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	return (1);
}

static void	print_env_error(char *arg)
{
	if (ft_strlen(arg) == 0)
		ft_dprintf(2, "minishell: export: `': not a valid identifier\n");
	else
		ft_dprintf(2, "minishell: export: %s: not a valid identifier\n", arg);
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
			errno = 0;
			free2(splited);
		}
		else
		{
			print_env_error(args[i]);
			fail_flag = 1;
		}
		i++;
	}
	return (fail_flag);
}
