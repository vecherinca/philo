/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:04:01 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/03 17:41:42 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	rightletter(char b)
{
	if (b == 'c' || b == 's' || b == '%')
		return (1);
	if (b == 'd' || b == 'i' || b == 'u')
		return (1);
	if (b == 'x' || b == 'X' || b == 'p')
		return (1);
	return (0);
}

int	pourcentage(char c, va_list *args)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(*args, int)));
	if (c == 'd' || c == 'i')
		return (ft_fornums('d', va_arg(*args, int)));
	if (c == 'u')
		return (ft_fornums('u', va_arg(*args, int)));
	if (c == 's')
		return (ft_putstr_fd(va_arg(*args, char *)));
	if (c == 'x')
		return (count_hex(va_arg(*args, unsigned int), 'x'));
	if (c == 'X')
		return (count_hex(va_arg(*args, unsigned int), 'X'));
	if (c == 'p')
		return (count_hex_p(va_arg(*args, unsigned long), 'p'));
	if (c == '%')
		return (ft_putchar_fd(37));
	return (0);
}

int	ft_printf(const char *string, ...)
{
	int		i;
	va_list	args;
	int		count;

	if (!string)
		return (-1);
	i = 0;
	count = 0;
	va_start(args, string);
	while (string[i])
	{
		if (string[i] == '%' && rightletter(string[i + 1]) && string[i] != '\0')
		{
			count += pourcentage(string[i + 1], &args);
			i++;
		}
		else if (string[i] != '%')
			count += write(1, &string[i], 1);
		else
			i++;
		i++;
	}
	va_end(args);
	return (count);
}
