/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:53:04 by yxu               #+#    #+#             */
/*   Updated: 2024/09/23 13:43:56 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fputp(int fd, void *p)
{
	write(fd, "0x", 2);
	if (((unsigned long)p) / 16 == 0)
		return (2 + ft_fputulnbr_base(fd, ((unsigned long)p) % 16,
				"0123456789abcdef"));
	return (2
		+ ft_fputulnbr_base(fd, ((unsigned long)p) / 16, "0123456789abcdef")
		+ ft_fputnbr_base(fd, ((unsigned long)p) % 16, "0123456789abcdef"));
}
