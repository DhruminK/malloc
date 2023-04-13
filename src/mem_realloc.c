/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:10:32 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/13 17:36:04 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*mem_realloc_new_ptr(t_list *pg, t_list *alloc,
		size_t size, t_page_info *pg_info)
{
	void	*new_addr;

	if (!alloc)
		return (0);
	if (g_gen_info.zone_alloc[0] && size < g_gen_info.zone_max[0])
		new_addr = zone_mem_alloc(size, &(g_gen_info.tiny));
	else if (g_gen_info.zone_alloc[1] && size < g_gen_info.zone_max[1])
		new_addr = zone_mem_alloc(size, &(g_gen_info.small));
	else
		new_addr = mem_alloc(size);
	if (!new_addr)
		return (0);
	if (size > alloc->size)
		size = alloc->size;
	ft_memcpy(new_addr, alloc->content, size);
	mem_dealloc_gen(pg, pg_info, alloc);
	return (new_addr);
}

int	mem_realloc(void *addr, size_t size, void **new_addr)
{
	t_list	*pg;
	t_list	*alloc;

	if (!addr)
		return (0);
	pg = 0;
	alloc = 0;
	if (find_addr(g_gen_info.large, addr, &pg, &alloc) < 1)
		return (-1);
	*new_addr = (mem_realloc_w_page(pg, alloc, size));
	if (*new_addr)
		return (1);
	*new_addr = mem_realloc_new_ptr(pg, alloc, size, 0);
	return (1);
}

int	zone_mem_realloc(void *addr, size_t size, void **new_addr)
{
	t_page_info	*pg_info[2];
	t_list		*alloc;
	int			i;
	int			ret;

	pg_info[0] = &(g_gen_info.tiny);
	pg_info[1] = &(g_gen_info.small);
	i = -1;
	while (++i < 2)
	{
		if (g_gen_info.zone_alloc[i] == 0)
			continue ;
		*new_addr = 0;
		alloc = 0;
		ret = find_addr_in_pg(pg_info[i], addr, &alloc);
		if (ret < 1)
			continue ;
		if (size < g_gen_info.zone_max[i])
			*new_addr = mem_realloc_in_page(pg_info[i], alloc, size);
		if (!*new_addr)
			*new_addr = mem_realloc_new_ptr(0, alloc, size, pg_info[i]);
		return (1);
	}
	return (0);
}
