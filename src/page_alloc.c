/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:16:56 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 17:52:19 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

t_list	*new_page_alloc(t_list **head, size_t size)
{
	void	*addr;
	t_list	*pg;

	if (!head)
		return (0);
	size += sizeof(t_list) + sizeof(t_page_info);
	addr = mmap_alloc(0, &size);
	if (!addr)
		return (0);
	pg = ft_lst_init_new_pg(addr, size);
	ft_lst_add_page_to_lst(head, &addr, pg);
	return ((t_list *)addr);
}

int	new_zone_alloc(size_t size, t_page_info *pg_info)
{
	void	*addr;

	if (!pg_info)
		return (-1);
	addr = mmap_alloc(0, &size);
	if (!addr)
		return (-1);
	pg_info->page_start = addr;
	pg_info->page_end = ((char *)addr) + size;
	pg_info->alloc_start = addr;
	pg_info->alloc = 0;
	return (0);
}

int	page_end_alloc(t_list *pg, size_t size)
{
	void		*addr;
	t_page_info	*pg_info;

	if (!pg)
		return (-1);
	pg_info = (t_page_info *)(pg->content);
	addr = mmap_alloc(pg_info->page_end, &size);
	if (!addr)
		return (0);
	pg_info->page_end = ((char *)(pg_info->page_end)) + size;
	ft_lst_merge_page_after(pg);
	return (1);
}
