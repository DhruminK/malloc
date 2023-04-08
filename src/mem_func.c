/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:04:55 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/08 15:16:50 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper_func.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	if (!src || !dst || !n)
		return (dst);
	d = (char *)dst;
	s = (char *)src;
	i = 0;
	while (++i <= n)
		d[i - 1] = s[i - 1];
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;
	size_t	i;

	if (!b || !len)
		return (b);
	i = 0;
	s = (char *)b;
	while (++i <= len)
		s[i - 1] = (char)c;
	return (b);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int8_t	dir;
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	dir = 1;
	if (src < dst && (src + len) > dst)
	{
		s = s + len - 1;
		d = d + len - 1;
		dir = -1;
	}
	i = 0;
	while (i < len)
	{
		*d = *s;
		s = s + dir;
		d = d + dir;
		i += 1;
	}
	return (dst);
}
