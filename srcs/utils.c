/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:33 by yxu               #+#    #+#             */
/*   Updated: 2024/09/01 16:30:25 by nakagawashi      ###   ########.fr       */
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

char	*ft_strndup(char *s, size_t n)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(s);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s, n);
	new_str[n] = '\0';
	return (new_str);
}

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char	*dst_ptr;

	dst_ptr = dst;
	while (*dst_ptr != '\0')
		dst_ptr++;
	while (n-- && *src != '\0')
		*dst_ptr++ = *src++;
	*dst_ptr = '\0';
	return (dst);
}
