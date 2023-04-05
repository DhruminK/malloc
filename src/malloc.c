/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:57:30 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 20:20:46 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

t_gen_info	g_gen_info;

void	*malloc(size_t size)
{
	void	*addr;

	if ((!(g_gen_info.is_tiny_alloc) || !(g_gen_info.is_small_alloc))
		&& (zone_init() == -1))
		return (0);
	addr = 0;
	if (size < TZ_MAX * g_gen_info.pg_size)
		addr = mem_alloc(&(g_gen_info.large), &(g_gen_info.tiny),
				size, 1);
	if (!addr && size < SZ_MAX * g_gen_info.pg_size)
		addr = mem_alloc(&(g_gen_info.large), &(g_gen_info.small),
				size, 1);
	if (!addr)
		addr = mem_alloc(&(g_gen_info.large), 0, size, 0);
	return (addr);
}
