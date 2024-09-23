/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:53:04 by yxu               #+#    #+#             */
/*   Updated: 2023/11/05 18:11:37 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putp(void *p)
{
	write(1, "0x", 2);
	if (((unsigned long)p) / 16 == 0)
		return (2 + ft_putulnbr_base(((unsigned long)p) % 16,
				"0123456789abcdef"));
	return (2 + ft_putulnbr_base(((unsigned long)p) / 16, "0123456789abcdef")
		+ ft_putnbr_base(((unsigned long)p) % 16, "0123456789abcdef"));
}
