/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:24:26 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/07 14:11:09 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	find_size_in_pg(t_page_info *pgi, size_t size, t_list **prev)
{
	size_t	len;

	if (!pgi || !prev)
		return (0);
	size += sizeof(t_list);
	if ((!(pgi->alloc) && (pgi->page_end - pgi->alloc_start) >= size)
		|| ((pgi->alloc) && (pgi->alloc - pgi->alloc_start) >= size))
		return (1);
	if (!(pgi->alloc))
		return (0);
	*prev = (t_list *)(pgi->alloc);
	while ((*prev)->next)
	{
		len = (size_t)((*prev)->next) - (size_t)((*prev)->content)
			- (*prev)->size;
		if ((void *)((*prev)->next) > (*prev)->content && len >= size)
			return (1);
		(*prev) = (*prev)->next;
	}
	len = pgi->page_end - (size_t)((*prev)->content) - (*prev)->size;
	if (len >= size)
		return (1);
	return (0);
}

int	find_size_w_next_pg(t_list *pg, size_t size, t_list **prev)
{
	t_page_info	*pg_info;
	size_t		addr;
	size_t		len;

	if (!pg || !prev)
		return (0);
	*prev = 0;
	pg_info = (t_page_info *)(pg->content);
	if (find_size_in_pg(pg_info, size, prev) == 1)
		return (1);
	if (!*prev)
		addr = pg_info->alloc_start;
	else
		addr = (size_t)((*prev)->content) + (*prev)->size;
	len = (size_t)(pg->next) - (size_t)(addr);
	if (pg->next && len + sizeof(t_list)
		+ sizeof(t_page_info) < size + sizeof(t_list))
		return (0);
	len = size - ((pg_info->page_end) - addr);
	if (pg->next && len + pg_info->page_end + PG_MARGIN >= (size_t)(pg->next))
		len = (size_t)pg->next - (pg_info->page_end);
	if (page_end_alloc(pg, len) == -1)
		return (0);
	return (1);
}

int	find_size(t_list *head, size_t size,
		t_list **pg, t_list **prev)
{
	if (!head || !pg || !prev)
		return (-1);
	(*pg) = head;
	while (*pg)
	{
		*prev = 0;
		if (find_size_w_next_pg(*pg, size, prev) == 1)
			return (1);
		*pg = (*pg)->next;
	}
	return (0);
}
