/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:25:43 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/07 17:12:07 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	size_to_pg(size_t *len, size_t pg_size, uint8_t ceil)
{
	size_t	s;

	if (!len || !pg_size)
		return ;
	s = ((size_t)(*len / pg_size)) * pg_size;
	if (ceil && *len % pg_size)
		s += pg_size;
	*len = s;
}

void	*mmap_alloc(void *addr, size_t size)
{
	size_t	pg_size;

	pg_size = getpagesize();
	if (!size)
		size = pg_size;
	if (((size_t)addr) % pg_size || size % pg_size)
		return (0);
	if (addr)
		addr = mmap(addr, size, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANON | MAP_FIXED, -1, 0);
	else
		addr = mmap(0, size, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANON, -1, 0);
	if (addr == MAP_FAILED)
		return (0);
	return (addr);
}

int	munmap_dealloc(void *addr, size_t size)
{
	size_t	pg_size;

	if (!addr || !size)
		return (-1);
	pg_size = getpagesize();
	if (((size_t)addr) % pg_size || size % pg_size)
		return (-1);
	if (munmap(addr, size) == -1)
		return (-1);
	return (0);
}
