/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:38:46 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/13 17:11:28 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*realloc(void *addr, size_t size)
{
	void	*new_addr;
	int		ret;

	if (!addr)
		return (malloc(size));
	new_addr = 0;
	ret = 0;
	if (g_gen_info.zone_alloc[0] || g_gen_info.zone_alloc[1])
		ret = zone_mem_realloc(addr, size, &new_addr);
	if (!ret)
		ret = mem_realloc(addr, size, &new_addr);
	return (new_addr);
}
