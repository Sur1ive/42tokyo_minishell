/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:48:40 by yxu               #+#    #+#             */
/*   Updated: 2024/09/23 13:53:50 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_dprint1f(int fd, va_list ap, char c)
{
	int	n;

	n = 0;
	if (c == 'c')
		n += ft_fputchar(fd, va_arg(ap, int));
	else if (c == 's')
		n += ft_fputstr(fd, va_arg(ap, char *));
	else if (c == 'p')
		n += ft_fputp(fd, va_arg(ap, void *));
	else if (c == 'd' || c == 'i')
		n += ft_fputnbr_base(fd, va_arg(ap, int), "0123456789");
	else if (c == 'u')
		n += ft_fputunbr_base(fd, va_arg(ap, unsigned int), "0123456789");
	else if (c == 'x')
		n += ft_fputunbr_base(fd, va_arg(ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		n += ft_fputunbr_base(fd, va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		n += ft_fputchar(fd, '%');
	return (n);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	ap;
	size_t	i;
	int		n;

	i = 0;
	n = 0;
	va_start(ap, str);
	while (str[i] && str[i + 1])
	{
		if (str[i] == '%')
		{
			n += ft_dprint1f(fd, ap, str[i + 1]);
			i += 2;
		}
		else
			n += ft_fputchar(fd, str[i++]);
	}
	if (str[i])
		n += ft_fputchar(fd, str[i]);
	va_end(ap);
	return (n);
}

// #include <stdio.h>
// #include <limits.h>
// int	main()
// {
// 	// char	*p = "Badsfjhasd12345";

// 	printf("return: %d\n",
// 		printf("   printf: c: %c s: %s i: %i d: %d p: %p u: %u X: %X %% ",
// 			126, NULL, INT_MAX, INT_MIN, (void *)ULONG_MAX, -1, -1));
// 	printf("return: %d\n",
// 		ft_printf("ft_printf: c: %c s: %s i: %i d: %d p: %p u: %u X: %X %% ",
// 			126, NULL, INT_MAX, INT_MIN, (void *)ULONG_MAX, -1, -1));
// }
