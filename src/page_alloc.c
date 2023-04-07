/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:54:00 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/07 14:14:43 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	ft_check_zone_alloc(size_t addr, size_t size)
{
	size_t		end;
	t_page_info	*pg_info;

	pg_info = &(g_gen_info.tiny);
	end = addr + size;
	if (pg_info->page_start <= addr && addr < pg_info->page_end)
		return (0);
	if (pg_info->page_start <= end && end < pg_info->page_end)
		return (0);
	if (addr <= pg_info->page_start && pg_info->page_start < end)
		return (0);
	if (addr <= pg_info->page_end && pg_info->page_end < end)
		return (0);
	return (0);
}

int	new_page_alloc(t_list **head, size_t size, t_list **e)
{
	void	*addr;

	if (!head || !e)
		return (-1);
	*e = 0;
	size = size + sizeof(t_list) + sizeof(t_page_info);
	size_to_pg(&size, (size_t)getpagesize(), 1);
	addr = mmap_alloc(0, size);
	if (!addr)
		return (-1);
	*e = new_pg_ele_init(addr, size);
	pg_add_to_lst(head, *e, e);
	return (0);
}

int	page_end_alloc(t_list *pg, size_t size)
{
	void		*addr;
	t_page_info	*pg_info;

	if (!pg || !size)
		return (-1);
	pg_info = (t_page_info *)(pg->content);
	addr = (void *)(pg_info->page_end);
	size_to_pg(&size, (size_t)getpagesize(), 1);
	if (ft_check_zone_alloc((size_t)addr, size) == 0
		|| addr + size > (void *)(pg->next))
		return (-1);
	if (mmap_alloc(addr, size) == 0)
		return (-1);
	pg_merge_after(pg);
	return (1);
}

int	new_zone_alloc(t_page_info *pg_info, size_t size)
{
	void	*addr;

	if (!pg_info)
		return (-1);
	if (!size)
		size = (size_t)getpagesize();
	size_to_pg(&size, (size_t)getpagesize(), 1);
	addr = mmap_alloc(0, size);
	if (!addr)
		return (-1);
	pg_info->page_start = (size_t)addr;
	pg_info->page_end = pg_info->page_start + size;
	pg_info->alloc_start = pg_info->page_start;
	pg_info->alloc = 0;
	return (1);
}
