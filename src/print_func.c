/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:06:51 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 16:33:49 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper_func.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, (unsigned char *)&c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s += 1;
	}
}

void	ft_putnbr_fd(long n, int fd)
{
	long	min;

	min = LONG_MIN;
	if (n == min)
		return (ft_putstr_fd("-9223372036854775808", fd));
	if (n < 0)
	{
		n = n * -1;
		write(fd, "-", 1);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void	ft_puthex_fd(size_t n, int fd, int is_prefix)
{
	size_t	r;

	if (!n)
		return (ft_putchar_fd('0', fd));
	if (is_prefix)
		write(fd, "0x", 2);
	if (n > 15)
		ft_puthex_fd(n / 16, fd, 0);
	r = n % 16;
	if (r < 10)
		ft_putchar_fd(r + '0', fd);
	else
		ft_putchar_fd(r - 10 + 'A', fd);
}

void	ft_putunbr_fd(size_t n, int fd)
{
	if (n > 9)
		ft_putunbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}
