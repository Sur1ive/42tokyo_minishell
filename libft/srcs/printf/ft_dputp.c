/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:53:04 by yxu               #+#    #+#             */
/*   Updated: 2024/10/07 16:06:35 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dputp(char *dest, void *p)
{
	int			len;
	uintptr_t	ptr;

	ptr = (uintptr_t)p;
	if (p == NULL)
		return (ft_dputstr(dest, "(nil)"));
	ft_memcpy(dest, "0x", 2);
	if (dest != NULL)
		dest += 2;
	if (ptr / 16 == 0)
		return (2 + ft_dputulnbr_base(dest, ptr % 16, "0123456789abcdef"));
	len = ft_dputulnbr_base(dest, ptr / 16, "0123456789abcdef");
	if (dest != NULL)
		dest += len;
	len += ft_dputulnbr_base(dest, ptr % 16, "0123456789abcdef");
	return (2 + len);
}
