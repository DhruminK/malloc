/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:08:36 by dkhatri           #+#    #+#             */
/*   Updated: 2023/03/30 16:08:52 by dkhatri          ###   ########.fr       */
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
