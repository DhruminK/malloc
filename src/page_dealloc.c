/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_dealloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:05:27 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 18:08:30 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	addr_div_pg_size(void **addr, char dir)
{
	size_t	rem;

	if (!addr)
		return ;
	rem = ((size_t)(*addr)) % ((size_t)(g_gen_info.pg_size));
	if (rem && dir)
		(*addr) += (g_gen_info.pg_size - rem);
	else if (rem)
		(*addr) -= (rem);
}

int	page_trim_end(t_page_info *pg_info)
{
	t_list		*alloc;
	void		*end;

	if (!pg_info)
		return (-1);
	alloc = pg_info->alloc;
	while (alloc->next)
		alloc = alloc->next;
	end = (void *)(alloc->content + alloc->size);
	addr_div_pg_size(&end, 1);
	if (end >= pg_info->page_end
		|| pg_info->page_end - end < g_gen_info.pg_size)
		return (0);
	if (munmap(end, (size_t)(pg_info->page_end - end)) == -1)
		return (-1);
	pg_info->page_end = end;
	return (0);
}

int	page_div_init_new_pg(t_list *pg, t_list *pg_next,
		t_list *alloc, void *start)
{
	t_page_info	*pg_info;
	t_page_info	*pg_next_info;

	if (!pg || !pg_next || !alloc)
		return (-1);
	pg_next->content = (void *)(pg_next + sizeof(t_list));
	pg_next->size = sizeof(t_page_info);
	pg_next->next = pg->next;
	pg->next = pg_next;
	pg_info = (t_page_info *)(pg->content);
	pg_next_info = (t_page_info *)(pg_next->content);
	pg_next_info->alloc_start = pg_next_info + sizeof(t_page_info);
	pg_next_info->alloc = alloc->next;
	alloc->next = 0;
	pg_next_info->page_start = pg_next;
	pg_next_info->page_end = pg_info->page_end;
	pg_info->page_end = start;
	return (0);
}

int	page_div(t_list *pg, t_list *alloc)
{
	void		*end;
	void		*start;

	if (!pg || !alloc || !(alloc->next))
		return (-1);
	start = alloc->content + alloc->size;
	end = alloc->next - sizeof(t_list) - sizeof(t_page_info);
	addr_div_pg_size(&end, 0);
	addr_div_pg_size(&start, 1);
	if ((size_t)(end - start) < (size_t)g_gen_info.pg_size)
		return (0);
	if (munmap(start, (size_t)(end - start)) == -1)
		return (-1);
	return (page_div_init_new_pg(pg, (t_list *)end, alloc, start));
}

int	page_dealloc_whole_pg(t_list *pg)
{
	t_list		*ele;
	t_page_info	*pg_info;
	t_list		*prev_pg;

	if (pg == g_gen_info.mem)
		prev_pg = 0;
	else
		prev_pg = g_gen_info.mem;
	while (prev_pg && prev_pg->next != pg)
		prev_pg = prev_pg->next;
	if (!prev_pg)
		ele = ft_lst_remove_front(&(g_gen_info.mem));
	else
		ele = ft_lst_remove_front(&(prev_pg->next));
	if (!ele)
		return (0);
	pg_info = (t_page_info *)(ele->content);
	if (munmap(pg_info->page_start,
			(size_t)(pg_info->page_end - pg_info->page_start)) == -1)
		return (-1);
	return (0);
}
