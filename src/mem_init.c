/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:51:27 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 20:20:58 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	zone_init(void)
{
	size_t	pg_size;

	g_gen_info.pg_size = getpagesize();
	pg_size = g_gen_info.pg_size;
	if (g_gen_info.is_tiny_alloc == 0
		&& new_zone_alloc(TZ_SIZE * pg_size, &(g_gen_info.tiny)) == -1)
		return (-1);
	g_gen_info.is_tiny_alloc = 1;
	if (g_gen_info.is_small_alloc == 0
		&& new_zone_alloc(SZ_SIZE * pg_size, &(g_gen_info.small)) == -1)
		return (-1);
	g_gen_info.is_small_alloc = 1;
	return (0);
}
