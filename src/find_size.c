/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:06:08 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/06 16:30:16 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	find_size_in_pg_alloc(t_page_info *pg_info, size_t size, t_list **prev)
{
	*prev = 0;
	size += sizeof(t_list);
	if (!(pg_info->alloc) && size <= (size_t)(pg_info->page_end
		- pg_info->page_start))
		return (1);
	if (!(pg_info->alloc))
		return (0);
	*prev = pg_info->alloc;
	while ((*prev)->next)
	{
		if (((size_t)((void *)(*prev)->next - (*prev)->content
			- (*prev)->size)) >= size)
			return (1);
		(*prev) = (*prev)->next;
	}
	if ((size_t)(pg_info->page_end - (*prev)->content - (*prev)->size) >= size)
		return (1);
	return (0);
}

int	find_size_w_next_page(t_list *pg, size_t size, t_list **prev)
{
	t_page_info	*pg_info;
	void		*addr;
	size_t		len;

	if (!pg)
		return (0);
	pg_info = (t_page_info *)(pg->content);
	if (find_size_in_pg_alloc(pg_info, size, prev) == 1)
		return (1);
	size += sizeof(t_list);
	if (!*prev)
		addr = pg_info->alloc_start;
	else
		addr = ((*prev)->content + (*prev)->size);
	len = size - (pg_info->page_end - addr);
	if ((size_t)((void *)pg->next + sizeof(t_list)
		+ sizeof(t_page_info) - pg_info->page_end) < size
		|| check_zone_alloc(pg_info->page_end, len) == 1)
		return (0);
	if (page_end_alloc(pg, len) < 1)
		return (0);
	return (1);
}

int	find_size(t_list *head, size_t size, t_list **prev, t_list **pg)
{
	int	ret;

	if (!pg || !head)
		return (0);
	(*pg) = head;
	while (*pg)
	{
		ret = find_size_w_next_page(*pg, size, prev);
		if (ret != 0)
			return (ret);
		(*pg) = (*pg)->next;
	}
	return (0);
}
