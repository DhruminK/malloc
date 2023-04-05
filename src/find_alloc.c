/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:52:27 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 20:31:41 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	find_alloc_in_page(t_page_info *pg_info, void *addr, t_list **alloc)
{
	if (!pg_info || !alloc)
		return (-1);
	if (!(pg_info->page_start <= addr && pg_info->page_end > addr))
		return (0);
	*alloc = pg_info->alloc;
	while (*alloc && ((*alloc)->content) != addr)
		(*alloc) = (*alloc)->next;
	if (*alloc)
		return (1);
	return (-1);
}

int	find_alloc_multi_page(t_list *p, void *addr, t_list **pg, t_list **alloc)
{
	t_page_info	*pg_info;

	if (!pg || !alloc || !addr || !p)
		return (-1);
	*pg = p;
	while (*pg)
	{
		pg_info = (t_page_info *)((*pg)->content);
		if (addr > (void *)(*pg) && (!((*pg)->next)
				|| (addr > (void *)(*pg) && addr < (void *)(*pg)->next)))
			return (find_alloc_in_page(pg_info, addr, alloc));
		if (addr < (void *)(*pg))
			break ;
		(*pg) = (*pg)->next;
	}
	return (-1);
}
