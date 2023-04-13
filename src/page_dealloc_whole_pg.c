/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_dealloc_whole_pg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:24:04 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/13 14:14:21 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	ft_first_pg_dealloc(t_list *pg)
{
	t_page_info	*pgi;
	size_t		addr;
	size_t		size;

	if (!pg || pg != g_gen_info.large)
		return ;
	pgi = (t_page_info *)(pg->content);
	if (pgi->page_end - pgi->page_start <= LZ_SIZE * g_gen_info.pg_size)
		return ;
	addr = pgi->page_start + LZ_SIZE * g_gen_info.pg_size;
	size_to_pg(&addr, g_gen_info.pg_size, 1);
	size = pgi->page_end - addr;
	if (size < g_gen_info.pg_size || munmap_dealloc((void *)addr, size) == -1)
		return ;
	pgi->page_end = addr;
}

void	ft_whole_pg_dealloc(t_list *pg)
{
	t_list		*e;
	t_page_info	*pgi;
	size_t		size;
	void		*next;

	if (!pg || pg == g_gen_info.large)
		return (ft_first_pg_dealloc(pg));
	next = pg->next;
	e = (g_gen_info.large);
	while (e && e->next != pg)
		e = e->next;
	if (!e)
		return ;
	pgi = (t_page_info *)(pg->content);
	size = (pgi->page_end - pgi->page_start);
	if (munmap_dealloc((void *)(pgi->page_start), size) == -1)
		return ;
	e->next = next;
}
