/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:20:16 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/03 00:17:11 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
Outputs the character ’c’ to the given file
descriptor.
*/
int	ft_putchar_fd(char c)
{
	write(1, &c, 1);
	return (1);
}
