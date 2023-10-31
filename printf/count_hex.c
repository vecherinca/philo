/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:29:39 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/02 23:19:25 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(unsigned long nbr, char *base)
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
		ft_putnbr_base(nbr, base);
		write(1, &ptnb, 1);
	}
}

int	count_hex(unsigned long nbr, char c)
{
	int	count;

	count = 0;
	if (nbr == 0 && c != 'p')
	{
		write(1, "0", 1);
		return (1);
	}
	if (c == 'x')
		ft_putnbr_base((unsigned long)nbr, "0123456789abcdef");
	else if (c == 'X')
		ft_putnbr_base((unsigned long)nbr, "0123456789ABCDEF");
	while (nbr != 0)
	{
		nbr = nbr / 16;
		count++;
	}
	return (count);
}
