/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_hex_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:29:39 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/02 23:18:53 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base_(unsigned long nbr, char *base)
{
	int	base_len;
	int	rem;
	int	ptnb;

	base_len = 16;
	if (nbr > 0)
	{
		rem = nbr % base_len;
		nbr = nbr / base_len;
		ptnb = base[rem];
		ft_putnbr_base_(nbr, base);
		write(1, &ptnb, 1);
	}
}

int	count_hex_p(unsigned long nbr, char c)
{
	int	count;

	count = 0;
	if (c == 'p')
	{
		if (nbr == 0)
		{
			write(1, "(nil)", 5);
			return (5);
		}
		write(1, "0x", 2);
		ft_putnbr_base_((unsigned long)nbr, "0123456789abcdef");
		count = 2;
	}
	while (nbr != 0)
	{
		nbr = nbr / 16;
		count++;
	}
	return (count);
}
