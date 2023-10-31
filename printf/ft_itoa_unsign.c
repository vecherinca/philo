/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 00:41:18 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/03 17:37:08 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_nmb_unsign(unsigned int n)
{
	unsigned int	i;

	i = 1;
	while (n / 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa_unsign(unsigned int n)
{
	char					*output;
	unsigned int			i;
	unsigned long int		num;

	num = (long)n;
	i = count_nmb_unsign(num) - 1;
	output = malloc(i + 1 * sizeof(char) + 1);
	if (!output)
		return (NULL);
	output[i + 1] = '\0';
	if (num == 0)
		output[0] = '0';
	while (num > 0)
	{
		output[i] = '0' + num % 10;
		num = num / 10;
		i--;
	}
	return (output);
}
