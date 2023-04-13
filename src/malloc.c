/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:15:09 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/13 15:09:50 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

t_gen_info	g_gen_info;

void	*malloc(size_t size)
{
	void	*addr;

	if (!(g_gen_info.zone_alloc[0]) || !(g_gen_info.zone_alloc[1]))
		zone_alloc_init();
	addr = 0;
	if (g_gen_info.zone_alloc[0] && size < g_gen_info.zone_max[0])
		addr = zone_mem_alloc(size, &(g_gen_info.tiny));
	if (!addr && g_gen_info.zone_alloc[1] && size < g_gen_info.zone_max[1])
		addr = zone_mem_alloc(size, &(g_gen_info.small));
	if (!addr)
		addr = mem_alloc(size);
	return (addr);
}
