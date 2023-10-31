/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fornums.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:29:54 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/03 17:38:13 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fornums(char c, int num)
{
	char	*s;
	int		p;

	if (c == 'd')
	{
		s = ft_itoa(num);
		p = ft_putstr_fd(s);
		free(s);
		return (p);
	}
	if (c == 'u')
	{
		s = ft_itoa_unsign((unsigned)num);
		p = ft_putstr_fd(s);
		free(s);
		return (p);
	}
	return (0);
}
