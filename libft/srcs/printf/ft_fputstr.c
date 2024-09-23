/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:03:12 by yxu               #+#    #+#             */
/*   Updated: 2024/09/23 13:35:56 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fputchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_fputstr(int fd, char *str)
{
	int	n;

	n = 0;
	if (!str)
		n += ft_fputstr(fd, "(null)");
	else
		while (str[n] != '\0')
			write(fd, &str[n++], 1);
	return (n);
}
