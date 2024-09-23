/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:44:11 by yxu               #+#    #+#             */
/*   Updated: 2024/09/23 13:39:04 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fwrite_num(int fd, long int num, char *base, int n)
{
	if (num >= n)
		ft_fwrite_num(fd, num / n, base, n);
	write(fd, &base[num % n], 1);
}

static size_t	ft_numlen(unsigned long num, size_t n)
{
	if (num >= n)
		return (ft_numlen(num / n, n) + 1);
	return (1);
}

int	ft_fputnbr_base(int fd, int nbr, char *base)
{
	int		n;
	long	num;

	num = nbr;
	n = 0;
	if (num < 0)
	{
		write(fd, "-", 1);
		n++;
		num = -num;
	}
	ft_fwrite_num(fd, num, base, ft_strlen(base));
	return (n + ft_numlen(num, ft_strlen(base)));
}

int	ft_fputunbr_base(int fd, unsigned int num, char *base)
{
	size_t	n;

	n = ft_strlen(base);
	if (num >= n)
		ft_fputunbr_base(fd, num / n, base);
	write(fd, &base[num % n], 1);
	return (ft_numlen(num, n));
}

int	ft_fputulnbr_base(int fd, unsigned long num, char *base)
{
	size_t	n;

	n = ft_strlen(base);
	if (num >= n)
		ft_fputulnbr_base(fd, num / n, base);
	write(fd, &base[num % n], 1);
	return (ft_numlen(num, n));
}
