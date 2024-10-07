/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:48:40 by yxu               #+#    #+#             */
/*   Updated: 2024/10/07 16:25:07 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_dprint1f(char *dest, va_list ap, char c)
{
	int	n;

	n = 0;
	if (c == 'c')
		n += ft_dputchar(dest, va_arg(ap, int));
	else if (c == 's')
		n += ft_dputstr(dest, va_arg(ap, char *));
	else if (c == 'p')
		n += ft_dputp(dest, va_arg(ap, void *));
	else if (c == 'd' || c == 'i')
		n += ft_dputnbr_base(dest, va_arg(ap, int), "0123456789");
	else if (c == 'u')
		n += ft_dputulnbr_base(dest, va_arg(ap, unsigned), "0123456789");
	else if (c == 'x')
		n += ft_dputulnbr_base(dest, va_arg(ap, unsigned), "0123456789abcdef");
	else if (c == 'X')
		n += ft_dputulnbr_base(dest, va_arg(ap, unsigned), "0123456789ABCDEF");
	else if (c == '%')
		n += ft_dputchar(dest, '%');
	return (n);
}

int	ft_printflen(const char *str, va_list ap)
{
	int		len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '%')
		{
			len += ft_dprint1f(NULL, ap, str[i + 1]);
			i += 2;
		}
		else
			len += ft_dputchar(NULL, str[i++]);
	}
	if (str[i])
		len += ft_dputchar(NULL, str[i]);
	return (len);
}

int	ft_destprintf(char *dest, const char *str, va_list ap)
{
	char	*dest_start;
	size_t	i;

	i = 0;
	dest_start = dest;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '%')
		{
			dest += ft_dprint1f(dest, ap, str[i + 1]);
			i += 2;
		}
		else
			dest += ft_dputchar(dest, str[i++]);
	}
	if (str[i])
		dest += ft_dputchar(dest, str[i]);
	return (dest - dest_start);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	ap;
	int		len;
	char	*dest;

	va_start(ap, str);
	len = ft_printflen(str, ap);
	va_end(ap);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (-1);
	dest[len] = '\0';
	va_start(ap, str);
	ft_destprintf(dest, str, ap);
	va_end(ap);
	write(fd, dest, len);
	free(dest);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		len;
	char	*dest;

	va_start(ap, str);
	len = ft_printflen(str, ap);
	va_end(ap);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (-1);
	dest[len] = '\0';
	va_start(ap, str);
	ft_destprintf(dest, str, ap);
	va_end(ap);
	write(1, dest, len);
	free(dest);
	return (len);
}
