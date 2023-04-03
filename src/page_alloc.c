/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 11:46:14 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 18:36:53 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	page_alloc_end(t_page_info *pg_info, size_t size)
{
	if (!pg_info || !size)
		return (-1);
	if (size < (size_t)g_gen_info.pg_size)
		return (0);
	if (alloc_mmap(pg_info->page_end, &size) == -1)
		return (-1);
	pg_info->page_end += size;
	return (0);
}

int	page_alloc_start(void)
{
	t_list		*pg;
	t_list		*ele;
	size_t		size;
	t_page_info	*pg_info;

	if (!g_gen_info.mem || g_gen_info.mem == (void *)LARGE_ADDR)
		return (0);
	pg = g_gen_info.mem;
	if ((size_t)(pg - LARGE_ADDR) < (size_t)g_gen_info.pg_size)
		return (0);
	size = (size_t)((void *)pg - (void *)LARGE_ADDR);
	if (alloc_mmap((void *)LARGE_ADDR, &size) == -1)
		return (-1);
	ele = (t_list *)LARGE_ADDR;
	ele->next = pg->next;
	ele->size = pg->size;
	ele->content = ele + sizeof(t_list);
	pg_info = (t_page_info *)(ele->content);
	ft_memcpy(pg_info, pg->content, sizeof(t_page_info));
	pg_info->page_start = (void *)LARGE_ADDR;
	pg_info->alloc_start = (void *)(LARGE_ADDR
			+ sizeof(t_list) + sizeof(t_page_info));
	g_gen_info.mem = (void *)LARGE_ADDR;
	return (0);
}

int	page_alloc_merge(t_list *pg)
{
	t_list		*pg_next;
	t_page_info	*pg_info;
	t_page_info	*pg_next_info;
	t_list		*alloc;
	size_t		len;

	if (!pg || !(pg->next))
		return (-1);
	pg_next = pg->next;
	pg_next_info = (t_page_info *)(pg_next->content);
	pg_info = (t_page_info *)(pg->content);
	len = pg_next_info->page_start - pg_info->page_end;
	if (alloc_mmap(pg_info->page_end, &len) == -1)
		return (-1);
	pg->next = pg_next->next;
	pg_info->page_end = pg_next_info->page_end;
	alloc = pg_info->alloc;
	while (alloc->next)
		alloc = alloc->next;
	alloc->next = pg_next_info->alloc;
	return (0);
}

static int	new_page_alloc_func(void *ref, void *content)
{
	if (content < ref)
		return (1);
	return (0);
}

int	new_page_alloc(t_list **pg, void **addr, size_t size)
{
	t_list		*ele;
	t_page_info	*pg_info;

	if (!pg || !addr || !size || !*addr)
		return (-1);
	size += sizeof(t_list) + sizeof(t_page_info);
	addr_div_pg_size(addr, 1);
	if (alloc_mmap(*addr, &size) == -1)
		return (-1);
	ele = *addr;
	ele->content = (*addr) + sizeof(t_list);
	ele->next = 0;
	ele->size = sizeof(t_page_info);
	pg_info = (t_page_info *)(ele->content);
	pg_info->page_start = ele;
	pg_info->page_end = (void *)(addr + size);
	pg_info->alloc = 0;
	pg_info->alloc_start = (void *)(ele->content + sizeof(t_page_info));
	ft_lst_add(pg, *addr, &new_page_alloc_func, ele);
	return (0);
}
