/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_dealloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:55:50 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/07 17:15:53 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	ft_whole_pg_dealloc(t_list *pg)
{
	t_list		*e;
	t_list		**addr;
	t_page_info	*pgi;
	size_t		size;
	void		*next;

	if (!pg)
		return ;
	e = (g_gen_info.large);
	next = pg->next;
	while (e && e == pg && e->next == pg)
		e = e->next;
	addr = &(g_gen_info.large);
	if (e->next != pg)
		addr = &(e->next);
	pgi = (t_page_info *)(pg->content);
	size = (pgi->page_end - pgi->page_start);
	if (munmap_dealloc((void *)pgi->page_start, size) == -1)
		return ;
	*addr = next;
}

void	ft_page_dealloc_start(t_list *pg)
{
	t_list		*e;
	t_page_info	pgi;
	t_page_info	*pg_i;
	t_list		**head;
	size_t		size;

	e = g_gen_info.large;
	while (e && e != pg && e->next != pg)
		e = e->next;
	head = &(g_gen_info.large);
	if (e && e != pg)
		head = &(e->next);
	ft_memcpy(&pgi, (pg->content), sizeof(t_page_info));
	size = pgi.alloc - pgi.alloc_start;
	size_to_pg(&size, (size_t)getpagesize(), 0);
	if (size < (size_t)getpagesize()
		|| munmap_dealloc((void *)pgi.page_start, size) == -1)
		return ;
	e = new_pg_ele_init((void *)(pgi.page_start + size),
			(pgi.page_end - pgi.page_start - size));
	*head = e;
	pg_i = (t_page_info *)(e->content);
	pg_i->alloc = pgi.alloc;
}

void	ft_page_dealloc_end(t_list *pg, t_list *prev)
{
	t_page_info	*pgi;
	size_t		size;
	size_t		addr;

	if (!pg)
		return ;
	pgi = (t_page_info *)(pg->content);
	if (!prev && (pgi->alloc))
		return (ft_page_dealloc_start(pg));
	if (!prev && !(pgi->alloc))
		return (ft_whole_pg_dealloc(pg));
	addr = (size_t)(prev->content) + prev->size;
	size_to_pg(&addr, (size_t)getpagesize(), 1);
	size = pgi->page_end - addr;
	if (munmap_dealloc((void *)addr, size) == -1)
		return ;
	pgi->page_end = addr;
}

void	ft_page_div(t_list *pg, t_list *prev)
{
	size_t		size;
	size_t		addr;
	t_list		*ele;
	t_page_info	*pgi;

	if (!prev || !(prev->next))
		return (ft_page_dealloc_end(pg, prev));
	pgi = (t_page_info *)(pg->content);
	addr = (size_t)(prev->content) + prev->size;
	size_to_pg(&addr, (size_t)getpagesize(), 1);
	if (addr > (size_t)prev->next)
		return ;
	size = (size_t)(prev->next) - addr
		- sizeof(t_list) - sizeof(t_page_info);
	size_to_pg(&addr, (size_t)getpagesize(), 0);
	if (munmap_dealloc((void *)addr, size) == -1)
		return ;
	ele = new_pg_ele_init((void *)(addr + size),
			(pgi->page_end - addr - size));
	ele->next = pg->next;
	pg->next = ele;
	pgi = (t_page_info *)(ele->content);
	pgi->alloc = (size_t)prev->next;
	prev->next = 0;
}
