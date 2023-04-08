/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:38:46 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/08 18:10:51 by dkhatri          ###   ########.fr       */
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
	if (g_gen_info.is_tiny_alloc)
		ret = zone_mem_realloc(addr, size, &(g_gen_info.tiny), &new_addr);
	if (!ret && g_gen_info.is_small_alloc)
		ret = zone_mem_realloc(addr, size, &(g_gen_info.small), &new_addr);
	if (!ret)
		ret = mem_realloc(addr, size, &new_addr);
	if (ret == -1)
		ft_str_frerror(addr);
	return (new_addr);
}
