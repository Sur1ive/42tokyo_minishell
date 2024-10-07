/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:16:05 by yxu               #+#    #+#             */
/*   Updated: 2024/10/07 14:02:55 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*buf;

	if (src == NULL || dst == NULL)
		return (NULL);
	buf = (unsigned char *)dst;
	while (n-- != 0)
		*buf++ = *(unsigned char *)src++;
	return (dst);
}
