/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 00:41:18 by mklimina          #+#    #+#             */
/*   Updated: 2022/11/29 18:21:19 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
In other words, turns integer into string.
*/
int	count_nmb(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i = 2;
		n = -n;
	}
	while (n / 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*output;
	int			i;
	long int	num;

	num = (long)n;
	i = count_nmb(num) - 1;
	output = malloc(i + 1 * sizeof(char) + 1);
	if (!output)
		return (NULL);
	output[i + 1] = '\0';
	if (num == 0)
		output[0] = '0';
	if (num < 0)
	{
		output[0] = 45;
		num = -1 * num;
	}
	while (num > 0)
	{
		output[i] = '0' + num % 10;
		num = num / 10;
		i--;
	}
	return (output);
}
