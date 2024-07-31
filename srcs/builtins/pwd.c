/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:52:12 by yxu               #+#    #+#             */
/*   Updated: 2024/07/31 14:52:54 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	workdir[PATH_MAX + 1];

	ft_memset(workdir, 0, PATH_MAX + 1);
	if (getcwd(workdir, PATH_MAX) == NULL)
	{
		printf("bash: pwd: %s\n", strerror(errno));
		return (1);
	}
	printf("%s\n", workdir);
	return (0);
}
