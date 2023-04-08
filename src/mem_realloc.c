/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:10:32 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/08 18:21:46 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*mem_realloc_new_ptr(t_list *pg, t_list *alloc,
		size_t size, t_page_info *pg_info)
{
	void		*new_addr;

	if (!alloc)
		return (0);
	new_addr = malloc(size);
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

int	zone_mem_realloc(void *addr, size_t size,
		t_page_info *pg_info, void **new_addr)
{
	t_list		*alloc;
	int			ret;

	if (!pg_info)
		return (-1);
	ret = find_addr_in_pg(pg_info, addr, &alloc);
	if (ret < 1)
		return (ret);
	*new_addr = mem_realloc_in_page(pg_info, alloc, size);
	if (*new_addr)
		return (1);
	*new_addr = mem_realloc_new_ptr(0, alloc, size, pg_info);
	return (1);
}
