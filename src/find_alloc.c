/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:38:46 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/07 17:18:29 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	find_addr_in_pg(t_page_info *pgi, void *addr, t_list **alloc)
{
	if (!pgi || !alloc)
		return (-1);
	if (!(pgi->page_start <= (size_t)addr && (size_t)addr < pgi->page_end))
		return (0);
	(*alloc) = (t_list *)pgi->alloc;
	while (*alloc)
	{
		if ((*alloc)->content == addr)
			return (1);
		if ((void *)(*alloc) > addr)
			return (-1);
		(*alloc) = (*alloc)->next;
	}
	return (-1);
}

int	find_addr(t_list *head, void *addr, t_list **pg, t_list **alloc)
{
	t_page_info	*pg_info;

	if (!pg || !alloc)
		return (-1);
	*pg = head;
	while (*pg)
	{
		pg_info = (t_page_info *)((*pg)->content);
		if ((void *)(*pg) > addr
				&& ((void *)(*pg)->next < addr || !((*pg)->next)))
			return (find_addr_in_pg(pg_info, addr, alloc));
		(*pg) = (*pg)->next;
	}
	return (0);
}
