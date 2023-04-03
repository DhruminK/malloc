/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_dealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:20:24 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 17:58:33 by dkhatri          ###   ########.fr       */
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
	e = pg_info->alloc;
	while (e && e != alloc && e->next != alloc)
		e = e->next;
	if (e == alloc)
		ft_lst_remove_front(&(pg_info->alloc));
	else
		ft_lst_remove_front(&(e->next));
	if (!(pg_info->alloc))
		return (page_dealloc_whole_pg(pg));
	if (!(alloc->next))
		return (page_trim_end(pg_info));
	return (page_div(pg, e));
}

int	ft_mem_dealloc_zone(t_list *alloc, t_page_info *pg_info)
{
	t_list	*e;

	if (!alloc || !pg_info)
		return (-1);
	e = pg_info->alloc;
	while (e && (e->next != alloc) && (e != alloc))
		e = e->next;
	if (e == alloc)
		ft_lst_remove_front(&(pg_info->alloc));
	else
		ft_lst_remove_front(&(e->next));
	return (0);
}
