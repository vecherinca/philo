/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:23:03 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/03 17:50:02 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
Outputs the string ’s’ to the given file
descriptor.
*/
int	ft_putstr_fd(char *s)
{
	int	i;
	int	count;

	if (s == NULL)
		return (ft_putstr_fd("(null)"));
	count = 0;
	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
		count++;
	}
	return (count);
}
