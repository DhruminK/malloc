/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:33:25 by dkhatri           #+#    #+#             */
/*   Updated: 2023/03/30 16:09:18 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	find_in_one_page(t_page_info *pg_info, size_t size, t_list **alloc)
{
	t_mem_alloc	*mem;

	if (!pg_info || !alloc || !size)
		return (-1);
	mem = (t_mem_alloc *)(pg_info->alloc->content);
	*alloc = 0;
	if ((size_t)(mem->start - 1 - pg_info->page_start) >= size)
		return (1);
	return (find_size(pg_info->alloc, pg_info->page_end, alloc, size));
}

int	find_with_next_page(t_list *pg, size_t size, t_list **alloc)
{
	t_page_info	*pg_info;
	t_page_info	*pg_info_next;
	t_mem_alloc	*mem;
	int			ret;

	if (!pg || !size || !alloc)
		return (-1);
	size += sizeof(t_mem_alloc) + sizeof(t_list);
	pg_info = (t_page_info *)(pg->content);
	ret = find_in_one_page(pg_info, size, alloc);
	if (ret != 0)
		return (ret);
	mem = (*alloc)->content;
	if (!(pg->next))
		return (new_page_alloc_end(pg_info, size, mem->end));
	pg_info_next = (t_page_info *)(pg->next->content);
	if ((size_t)(pg_info_next->alloc_start - mem->end) >= size)
		return (new_page_alloc(pg, size));
	return (0);
}

void	*no_pages_to_find(size_t size)
{
	t_page_info	*pg;
	t_mem_alloc	*mem;

	if (!size || g_gen_info.mem)
		return (0);
	if (new_page_start_alloc((void *)LARGE_ADDR, size, &(g_gen_info.mem)) == -1)
		return (0);
	pg = (t_page_info *)(g_gen_info.mem->content);
	if (ft_insert_mem_info(0, pg->alloc_start, size, &(pg->alloc)) == -1)
		return (0);
	mem = (t_mem_alloc *)(pg->alloc->content);
	return (mem->data_start);
}

void	*space_found_in_pages(t_list *alloc, size_t size,
		t_page_info *pg)
{
	t_list		*ele;
	t_mem_alloc	*mem;

	if (!alloc || !pg || !size)
		return (0);
	if (ft_insert_mem_info(alloc, pg->alloc_start, size, &(pg->alloc)) == -1)
		return (0);
	if (alloc)
		ele = alloc->next;
	else
		ele = pg->alloc;
	mem = (t_mem_alloc *)(ele->content);
	return (mem->data_start);
}

void	*find_in_pages(size_t size)
{
	t_list		*pg;
	t_page_info	*p;
	int			ret;
	t_list		*alloc;

	if (!size)
		return (0);
	if (!(g_gen_info.mem))
		return (no_pages_to_find(size));
	pg = g_gen_info.mem;
	while (pg)
	{
		alloc = 0;
		ret = find_with_next_page(pg, size, &alloc);
		if (ret == -1)
			return (0);
		p = (t_page_info *)(pg->content);
		if (ret == 1)
			return (space_found_in_pages(alloc, size, p));
		pg = pg->next;
	}
	return (0);
}
