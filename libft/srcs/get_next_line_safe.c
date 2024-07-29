/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_safe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:14:39 by yxu               #+#    #+#             */
/*   Updated: 2023/11/05 18:14:11 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strlen_sp(const char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	char	*start;
	size_t	i;

	str = (char *)malloc(strlen_sp((char *)s1) + strlen_sp((char *)s2) + 1);
	if (str == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	start = str;
	i = 0;
	while (s1 && s1[i] != '\0')
		*str++ = s1[i++];
	i = 0;
	while (s2 && s2[i] != '\0')
		*str++ = s2[i++];
	*str = '\0';
	free(s1);
	free(s2);
	return (start);
}

static char	*ft_free2(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*get_next_line_intialized(int fd, char *line, char *buf)
{
	ssize_t		flag;
	long long	i;

	i = BUFFER_SIZE;
	flag = 1;
	while (flag != 0 && !(buf && buf[i - 1] == '\n'))
	{
		if (i == BUFFER_SIZE)
		{
			line = ft_strjoin_free(line, buf);
			buf = (char *)malloc(BUFFER_SIZE + 1);
			if (line == NULL || buf == NULL)
				return (ft_free2(line, buf));
			buf[0] = 0;
			i = 0;
		}
		flag = read(fd, buf + i++, 1);
		if (flag == -1)
			return (ft_free2(line, buf));
		buf[i] = 0;
	}
	line = ft_strjoin_free(line, buf);
	if (strlen_sp(line) == 0 && flag == 0)
		return (ft_free2(line, NULL));
	return (line);
}

char	*get_next_line(int fd)
{
	if ((long long)BUFFER_SIZE <= 0 || BUFFER_SIZE >= (long long)INT_MAX)
		return (NULL);
	return (get_next_line_intialized(fd, NULL, NULL));
}
