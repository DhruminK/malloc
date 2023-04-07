/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:15:09 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/07 14:13:55 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

t_gen_info	g_gen_info;

void	*malloc(size_t size)
{
	void	*addr;

	if ((!g_gen_info.is_tiny_alloc || !g_gen_info.is_small_alloc)
		&& zone_alloc_init() == -1)
		return (0);
	addr = 0;
	if (g_gen_info.is_tiny_alloc && size < TZ_MAX * g_gen_info.pg_size)
		addr = zone_mem_alloc(size, &(g_gen_info.tiny));
	if (!addr && g_gen_info.is_small_alloc
		&& size < SZ_MAX * g_gen_info.pg_size)
		addr = zone_mem_alloc(size, &(g_gen_info.small));
	if (!addr)
		addr = mem_alloc(size);
	return (addr);
}
