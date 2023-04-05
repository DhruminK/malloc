/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_dealloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:00:17 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 20:27:30 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	page_div(t_list *pg, t_list *prev)
{
	void	*addr;
	size_t	size;

	if (!pg || !prev || !(prev->next))
		return ;
	addr = (char *)(prev->content) + prev->size;
	size_to_pg((size_t *)(&addr), g_gen_info.pg_size, 1);
	size = (size_t)((char *)(prev->next) - (char *)addr);
	size -= sizeof(t_list) - sizeof(t_page_info);
	size_to_pg(&size, g_gen_info.pg_size, 0);
	if (size < g_gen_info.pg_size)
		return ;
	ft_page_div(pg, prev, addr, size);
	return ;
}

void	page_end_dealloc(t_page_info *pg_info, t_list *prev)
{
	void	*addr;
	size_t	size;

	if (!pg_info || !prev || prev->next)
		return ;
	addr = (char *)(prev->content) + prev->size;
	size_to_pg((size_t *)(&addr), g_gen_info.pg_size, 1);
	size = (size_t)((char *)(pg_info->page_end) - (char *)(addr));
	if (size % g_gen_info.pg_size)
		return ;
	if (munmap(addr, size) == -1)
		return ;
	pg_info->page_end = addr;
}

void	whole_page_dealloc(t_list **pg)
{
	t_page_info	*pg_info;
	void		*addr;
	void		*next_pg;
	size_t		size;

	if (!pg || !*pg)
		return ;
	next_pg = (*pg)->next;
	pg_info = (t_page_info *)((*pg)->content);
	if (pg_info->alloc)
		return ;
	addr = (pg_info->page_start);
	size = pg_info->page_end - pg_info->page_start;
	if (size % g_gen_info.pg_size)
		return ;
	if (munmap(addr, size) == -1)
		return ;
	(*pg) = next_pg;
}

void	page_dealloc_start(t_list **pg)
{
	t_page_info	pg_i;
	t_page_info	*pg_info;
	size_t		size;
	size_t		len;
	t_list		*ele;

	if (!pg || !*pg)
		return ;
	ft_memcpy(&pg_i, (*pg)->content, sizeof(t_page_info));
	if (!(pg_i.alloc))
		return (whole_page_dealloc(pg));
	size = (char *)(pg_i.alloc) - (char *)(pg_i.alloc_start);
	size_to_pg(&size, g_gen_info.pg_size, 0);
	if (munmap(pg_i.page_start, size) == -1)
		return ;
	len = (size_t)(pg_i.page_end - pg_i.page_start) - size;
	ele = ft_lst_init_new_pg(pg_i.page_start + size, len);
	pg_info = (t_page_info *)(ele->content);
	pg_info->alloc = pg_i.alloc;
	*pg = ele;
}

void	page_dealloc(t_list *pg, t_list *prev)
{
	t_list		*ele;
	t_page_info	*pg_info;

	if (!pg)
		return ;
	if (!prev)
	{
		ele = g_gen_info.large;
		while (ele && (ele != pg) && (ele->next != pg))
			ele = ele->next;
		if (ele == pg)
			return (page_dealloc_start(&(g_gen_info.large)));
		return (page_dealloc_start(&(ele->next)));
	}
	if (prev->next)
		return (page_div(pg, prev));
	pg_info = (t_page_info *)(pg->content);
	return (page_end_dealloc(pg_info, prev));
}
