/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:57:22 by dkhatri           #+#    #+#             */
/*   Updated: 2023/03/30 16:10:35 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	new_page_alloc_end(t_page_info *pg_info, size_t size, void *alloc_end)
{
	size_t	len;

	if (!pg_info || !size || !alloc_end)
		return (-1);
	if ((size_t)(pg_info->page_end - alloc_end) >= size)
		return (0);
	len = size - (pg_info->page_end - alloc_end);
	if (alloc_mmap(pg_info->page_end, &len) == -1)
		return (-1);
	pg_info->page_end += len;
	return (1);
}

int	new_page_alloc_merge(t_list *pg)
{
	t_page_info	*pg_info;
	t_page_info	*pg_info_next;
	t_list		*alloc;
	size_t		len;

	if (!pg || !(pg->next))
		return (-1);
	pg_info = (t_page_info *)(pg->content);
	pg_info_next = (t_page_info *)(pg->next->content);
	len = pg_info_next->page_start - pg_info->page_end;
	if (alloc_mmap(pg_info->page_end, &len) == -1)
		return (-1);
	pg_info->page_end = pg_info_next->page_end;
	alloc = pg_info->alloc;
	while (alloc->next)
		alloc = alloc->next;
	alloc->next = pg_info_next->alloc;
	ft_memset(pg_info_next, 0, sizeof(t_page_info));
	pg->next = pg->next->next;
	return (1);
}

int	new_page_alloc(t_list *pg, size_t size)
{
	t_page_info	*pg_info;
	t_page_info	*pg_info_next;
	t_mem_alloc	*a;
	t_list		*alloc;

	if (!pg || !size)
		return (-1);
	pg_info = (t_page_info *)(pg->content);
	alloc = pg_info->alloc;
	while (alloc->next)
		alloc = alloc->next;
	a = (t_mem_alloc *)(alloc->content);
	if (!(pg->next))
		return (new_page_alloc_end(pg_info, size, a->end));
	pg_info_next = (t_page_info *)(pg->next->content);
	if ((size_t)(pg_info_next->page_start - a->end) > size)
		return (new_page_alloc_end(pg_info, size, a->end));
	return (new_page_alloc_merge(pg));
}

int	new_page_start_alloc(void *addr, size_t size, t_list **alloc)
{
	t_list		*e;
	t_page_info	pg;
	t_page_info	*p;

	pg.page_end = (void *)(size + sizeof(t_mem_alloc) + sizeof(t_list)
			+ sizeof(t_page_info) + sizeof(t_list));
	if (alloc_mmap(addr, (size_t *)&(pg.page_end)) == -1)
		return (-1);
	e = (t_list *)addr;
	e->content = addr + sizeof(t_list);
	e->size = sizeof(t_page_info);
	e->next = 0;
	pg.page_start = e;
	pg.alloc_start = pg.page_start + sizeof(t_page_info) + sizeof(t_list);
	pg.alloc = 0;
	p = (t_page_info *)(e->content);
	ft_memcpy(p, &pg, sizeof(t_page_info));
	if (alloc)
		*alloc = e;
	return (0);
}
