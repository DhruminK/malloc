/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:19:04 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 14:18:00 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	size_to_pg(size_t *s, size_t pg_size, int ceil)
{
	size_t	size;

	if (!s || !pg_size)
		return ;
	size = ((size_t)(*s / pg_size)) * pg_size;
	if (ceil && (*s % pg_size))
		size += pg_size;
	*s = size;
}

void	*mmap_alloc(void *addr, size_t *size)
{
	size_t	pg_size;
	void	*p;

	pg_size = getpagesize();
	if (!*size)
		*size = pg_size;
	size_to_pg(size, pg_size, 1);
	if (addr)
		p = mmap(addr, *size, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_FIXED | MAP_PRIVATE, -1, 0);
	else
		p = mmap(0, *size, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
	if (p == MAP_FAILED)
		return (0);
	return (p);
}

int	check_zone_alloc(void *addr, size_t size)
{
	void		*end;
	t_page_info	*pg_info;

	end = addr + size;
	pg_info = &(g_gen_info.tiny);
	if ((pg_info->page_start <= addr && pg_info->page_end >= addr)
		|| (pg_info->page_start <= end && pg_info->page_end >= end))
		return (1);
	pg_info = &(g_gen_info.small);
	if ((pg_info->page_start <= addr && pg_info->page_end >= addr)
		|| (pg_info->page_start <= end && pg_info->page_end >= end))
		return (1);
	return (0);
}
