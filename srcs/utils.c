/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:33 by yxu               #+#    #+#             */
/*   Updated: 2024/08/06 21:05:18 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free char **
void	free2(char **p)
{
	int	i;

	if (p == NULL)
		return ;
	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*str;
	char	*start;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	start = str;
	if (str == NULL)
		return (NULL);
	while (*s1 != '\0')
		*str++ = *s1++;
	while (*s2 != '\0')
		*str++ = *s2++;
	while (*s3 != '\0')
		*str++ = *s3++;
	*str = '\0';
	return (start);
}

int	ft_count(char **p)
{
	int	count;

	count = 0;
	while (p && p[count])
		count++;
	return (count);
}
