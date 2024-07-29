/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:44:11 by yxu               #+#    #+#             */
/*   Updated: 2023/11/05 18:11:35 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write_num(long int num, char *base, int n)
{
	if (num >= n)
		ft_write_num(num / n, base, n);
	write(1, &base[num % n], 1);
}

static size_t	ft_numlen(unsigned long num, size_t n)
{
	if (num >= n)
		return (ft_numlen(num / n, n) + 1);
	return (1);
}

int	ft_putnbr_base(int nbr, char *base)
{
	int		n;
	long	num;

	num = nbr;
	n = 0;
	if (num < 0)
	{
		write(1, "-", 1);
		n++;
		num = -num;
	}
	ft_write_num(num, base, ft_strlen(base));
	return (n + ft_numlen(num, ft_strlen(base)));
}

int	ft_putunbr_base(unsigned int num, char *base)
{
	size_t	n;

	n = ft_strlen(base);
	if (num >= n)
		ft_putunbr_base(num / n, base);
	write(1, &base[num % n], 1);
	return (ft_numlen(num, n));
}

int	ft_putulnbr_base(unsigned long num, char *base)
{
	size_t	n;

	n = ft_strlen(base);
	if (num >= n)
		ft_putulnbr_base(num / n, base);
	write(1, &base[num % n], 1);
	return (ft_numlen(num, n));
}
