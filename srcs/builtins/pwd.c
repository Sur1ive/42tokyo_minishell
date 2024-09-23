/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:52:12 by yxu               #+#    #+#             */
/*   Updated: 2024/09/23 14:09:53 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	workdir[PATH_MAX + 1];

	ft_memset(workdir, 0, PATH_MAX + 1);
	if (getcwd(workdir, PATH_MAX) == NULL)
	{
		ft_dprintf(2, "minishell: pwd: %s\n", strerror(errno));
		errno = 0;
		return (1);
	}
	printf("%s\n", workdir);
	return (0);
}
