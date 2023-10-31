/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:39:59 by mklimina          #+#    #+#             */
/*   Updated: 2022/12/03 17:50:32 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

int			ft_printf(const char *string, ...);
char		ft_putnbr_fd(int nb);
int			ft_putstr_fd(char *s);
int			ft_putchar_fd(char c);
char		*ft_itoa(int n);
char		*ft_itoa_unsign(unsigned int n);
int			count_hex(unsigned long nbr, char c);
int			count_hex_p(unsigned long nbr, char c);
int			ft_fornums(char c, int num);
#endif