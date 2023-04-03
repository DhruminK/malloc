/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:54:50 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 18:00:16 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*mem_realloc(t_list *alloc, t_list *pg, size_t size)
{
	void	*addr;

	if (!alloc || !pg || !size)
		return (0);
	addr = find_realloc(alloc, pg, size, 0);
	if (addr)
		return (addr);
	addr = malloc(size);
	if (!addr)
		return (0);
	ft_mem_dealloc(alloc, pg);
	return (addr);
}

void	*mem_alloc_zone(t_list *alloc, t_page_info *pg_info, size_t size)
{
	void	*addr;

	if (!alloc || !pg_info || !size)
		return (0);
	if (find_realloc_same_ele_pg(alloc, pg_info, size) == 1)
	{
		alloc->size = size;
		return (alloc->content);
	}
	addr = malloc(size);
	if (!addr)
		return (0);
	ft_memcpy(addr, alloc->content, alloc->size);
	ft_mem_dealloc_zone(alloc, pg_info);
	return (addr);
}
