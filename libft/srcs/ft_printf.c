/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:48:40 by yxu               #+#    #+#             */
/*   Updated: 2023/11/05 18:11:31 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print1f(va_list ap, char c)
{
	int	n;

	n = 0;
	if (c == 'c')
		n += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		n += ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
		n += ft_putp(va_arg(ap, void *));
	else if (c == 'd' || c == 'i')
		n += ft_putnbr_base(va_arg(ap, int), "0123456789");
	else if (c == 'u')
		n += ft_putunbr_base(va_arg(ap, unsigned int), "0123456789");
	else if (c == 'x')
		n += ft_putunbr_base(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		n += ft_putunbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		n += ft_putchar('%');
	return (n);
}

int	ft_printf(const char *str, ...)
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
			n += ft_print1f(ap, str[i + 1]);
			i += 2;
		}
		else
			n += ft_putchar(str[i++]);
	}
	if (str[i])
		n += ft_putchar(str[i]);
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
