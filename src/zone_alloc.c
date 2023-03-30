/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:10:15 by dkhatri           #+#    #+#             */
/*   Updated: 2023/03/30 16:11:29 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	zone_init(void)
{
	size_t	len;

	if (g_gen_info.is_alloc)
		return (-1);
	g_gen_info.tiny.start = (void *)TINY_ADDR;
	g_gen_info.tiny.end = (void *)SMALL_ADDR;
	g_gen_info.tiny.max = TINY_MAX;
	g_gen_info.small.start = (void *)SMALL_ADDR;
	g_gen_info.small.end = (void *)LARGE_ADDR;
	g_gen_info.small.max = SMALL_MAX;
	len = SMALL_ADDR - TINY_ADDR;
	if (alloc_mmap(g_gen_info.tiny.start, &len) == -1)
		return (-1);
	len = LARGE_ADDR - SMALL_ADDR;
	if (alloc_mmap(g_gen_info.small.start, &len) == -1)
		return (-1);
	g_gen_info.is_alloc = 1;
	g_gen_info.mem = 0;
	return (0);
}

void	*malloc(size_t size)
{
	void		*p;

	if (!size)
		return (0);
	if (!(g_gen_info.is_alloc) && zone_init() == -1)
		return (0);
	p = 0;
	if (size + sizeof(t_list) + sizeof(t_mem_alloc) < g_gen_info.tiny.max)
		p = zone_mem_alloc(size, &(g_gen_info.tiny));
	if (!p && (size + sizeof(t_list) + sizeof(t_mem_alloc)
			< g_gen_info.small.max))
		p = zone_mem_alloc(size, &(g_gen_info.small));
	if (!p)
		p = find_in_pages(size);
	return (p);
}
