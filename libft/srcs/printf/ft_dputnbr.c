/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:44:11 by yxu               #+#    #+#             */
/*   Updated: 2024/10/07 16:07:01 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_dwrite_num(char *dest, unsigned long num, char *base, int n)
{
	int	offset;

	if (num >= (unsigned long)n)
		offset = ft_dwrite_num(dest, num / n, base, n);
	else
		offset = 0;
	dest += offset;
	ft_memcpy(dest, &base[num % n], 1);
	return (offset + 1);
}

static size_t	ft_numlen(unsigned long num, size_t n)
{
	if (num >= n)
		return (ft_numlen(num / n, n) + 1);
	return (1);
}

int	ft_dputnbr_base(char *dest, int nbr, char *base)
{
	int		sign;
	long	num;

	num = nbr;
	if (dest == NULL && num < 0)
		return (1 + ft_numlen(-num, ft_strlen(base)));
	else if (dest == NULL && num >= 0)
		return (ft_numlen(num, ft_strlen(base)));
	sign = 0;
	if (num < 0)
	{
		ft_memcpy(dest++, "-", 1);
		sign = 1;
		num = -num;
	}
	return (sign + ft_dwrite_num(dest, num, base, ft_strlen(base)));
}

int	ft_dputulnbr_base(char *dest, unsigned long num, char *base)
{
	if (dest == NULL)
		return (ft_numlen(num, ft_strlen(base)));
	return (ft_dwrite_num(dest, num, base, ft_strlen(base)));
}
