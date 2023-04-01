/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_dealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:20:24 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/01 17:09:36 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	ft_mem_dealloc(t_list *alloc, t_list *pg)
{
	t_page_info	*pg_info;
	t_list		*e;

	if (!alloc || !pg)
		return (-1);
	pg_info = (t_page_info *)(pg->content);
	if (pg_info->alloc == alloc && alloc->next == 0)
		return (page_dealloc_whole_pg(pg));
	e = pg_info->alloc;
	while (e && (e->next != alloc))
		e = e->next;
	if (!e)
		return (-1);
	e->next = alloc->next;
	if (!(alloc->next))
		return (page_trim_end(pg_info));
	return (page_div(pg, e));
}
