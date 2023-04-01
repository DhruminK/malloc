/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:54:27 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/01 16:02:42 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	find_alloc_in_page(void *addr, t_list *pg, t_list **alloc)
{
	if (!addr || !pg || !alloc)
		return (-1);
	(*alloc) = pg->alloc;
	while (*alloc)
	{
		if ((*alloc)->content == addr)
			return (1);
		if ((*alloc) > addr)
			return (-1);
		(*alloc) = (*alloc)->next;
	}
	return (0);
}

int	find_alloc(void *addr, t_list **pg, t_list **alloc)
{
	int	ret;
	if (!addr || !pg || !alloc)
		return (-1);
	(*pg) = g_gen_info.mem;
	while (*pg)
	{
		ret = find_alloc_in_page(addr, *pg, alloc);
		if (ret != 0)
			return (ret);
		*pg = (*pg)->next;
	}
	return (-1);
}
