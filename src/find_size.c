/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:32:24 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 18:36:38 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	find_size_start(size_t size)
{
	if ((void *)LARGE_ADDR == g_gen_info.mem)
		return (0);
	if (g_gen_info.mem == 0)
		return (1);
	if (((size_t)g_gen_info.mem) - LARGE_ADDR >= size + sizeof(t_list))
		return (1);
	return (0);
}

int	find_size_page(size_t size, t_page_info *pg_info, t_list **a)
{
	size_t	len;

	if (!pg_info)
		return (0);
	size += sizeof(t_list);
	*a = 0;
	if (!pg_info->alloc && (size <= (size_t)(pg_info->page_end
			- pg_info->page_start)))
		return (1);
	if ((size_t)((void *)pg_info->alloc - pg_info->alloc_start) >= size)
		return (1);
	*a = (pg_info->alloc);
	while ((*a)->next)
	{
		len = ((void *)(*a)->next) - (*a)->content - (*a)->size;
		if (len >= size)
			return (1);
		*a = (*a)->next;
	}
	if ((size_t)(pg_info->page_end - ((*a)->content + (*a)->size)) >= size)
		return (1);
	return (0);
}

int	find_size_page_end(size_t size, t_list *end, t_list *pg)
{
	t_page_info	*pg_info;
	t_page_info	*pg_next_info;
	void		*len;

	if (!pg || !end || !size)
		return (0);
	size += sizeof(t_list);
	if (pg->next == 0)
		return (1);
	pg_info = (t_page_info *)(pg->content);
	pg_next_info = (t_page_info *)(pg->next->content);
	len = end->content + end->size;
	if ((size_t)(pg_next_info->alloc_start - len) >= size)
		return (1);
	return (0);
}

int	find_size(size_t size, t_list **pg, t_list **alloc)
{
	t_page_info	*pg_info;

	if (!size || !pg || !alloc)
		return (-1);
	if (find_size_start(size) == 1)
		return (1);
	*pg = (g_gen_info.mem);
	while (*pg)
	{
		pg_info = (t_page_info *)((*pg)->content);
		if (find_size_page(size, pg_info, alloc) == 1)
			return (2);
		if (find_size_page_end(size, *alloc, *pg) == 1)
			return (3);
		(*pg) = (*pg)->next;
	}
	return (0);
}
