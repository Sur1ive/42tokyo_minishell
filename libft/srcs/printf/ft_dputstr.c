/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:03:12 by yxu               #+#    #+#             */
/*   Updated: 2024/10/07 16:06:19 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dputchar(char *dest, char c)
{
	ft_memcpy(dest, &c, 1);
	return (1);
}

int	ft_dputstr(char *dest, char *str)
{
	if (!str)
		return (ft_dputstr(dest, "(null)"));
	else
		ft_memcpy(dest, str, ft_strlen(str));
	return (ft_strlen(str));
}
