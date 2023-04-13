/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:38:13 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/13 17:14:36 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	free(void *addr)
{
	int	ret;

	ret = 0;
	if (g_gen_info.zone_alloc[0])
		ret = zone_mem_dealloc(addr, &(g_gen_info.tiny));
	if (!ret && g_gen_info.zone_alloc[1])
		ret = zone_mem_dealloc(addr, &(g_gen_info.small));
	if (!ret)
		ret = mem_dealloc(addr);
}
