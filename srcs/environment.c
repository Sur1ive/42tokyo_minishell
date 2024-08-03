/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:27:09 by yxu               #+#    #+#             */
/*   Updated: 2024/08/03 17:57:35 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_extend(char **envp)
{
	int		count;
	char	**dup;
	int		i;

	count = ft_count(envp);
	dup = malloc((count + 2) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i++])
		{
			free2(dup);
			return (NULL);
		}
	}
	dup[count] = NULL;
	dup[count + 1] = NULL;
	return (dup);
}

char	**ft_getenv_item(char **envp, char *name)
{
	int	i;

	if (envp == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

char	*ft_getenv(char **envp, char *name)
{
	char	**env_item;

	if (envp == NULL)
		return ("");
	env_item = ft_getenv_item(envp, name);
	if (env_item == NULL)
		return (NULL);
	return (*env_item + ft_strlen(name) + 1);
}

static int	ft_addenv(char ***envpp, char *name, char *value)
{
	char	**new_envp;
	char	**envp;

	envp = *envpp;
	new_envp = env_extend(envp);
	if (new_envp == NULL)
		return (-1);
	new_envp[ft_count(envp)] = ft_strjoin3(name, "=", value);
	if (new_envp[ft_count(envp)] == NULL)
	{
		free2(new_envp);
		return (-1);
	}
	free2(envp);
	*envpp = new_envp;
	return (0);
}

int	ft_setenv(char ***envpp, char *name, char *value)
{
	char	**env_item;
	char	**envp;

	if (envpp == NULL || name == NULL || value == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	envp = *envpp;
	env_item = ft_getenv_item(envp, name);
	if (env_item != NULL)
	{
		free(*env_item);
		*env_item = ft_strjoin3(name, "=", value);
		if (*env_item == NULL)
			return (-1);
	}
	else
	{
		if (ft_addenv(envpp, name, value) == -1)
			return (-1);
	}
	return (0);
}
