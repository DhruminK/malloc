/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:13:14 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 17:52:07 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*mem_alloc_init(t_list *prev, t_page_info *pg_info, size_t size)
{
	t_list	*ele;
	t_list	**addr;

	if (!prev && !pg_info)
		return (0);
	if (prev)
		ele = (t_list *)(prev->content + prev->size);
	else if (!prev && pg_info->alloc)
		ele = (t_list *)(pg_info->alloc - size - sizeof(t_list));
	else
		ele = (t_list *)(pg_info->alloc_start);
	ele->content = ((char *)ele) + sizeof(t_list);
	ele->size = size;
	if (prev)
		addr = &(prev->next);
	else
		addr = &(pg_info->alloc);
	ft_lst_add_front(addr, ele);
	return (ele->content);
}

void	*mem_alloc(t_list **head, t_page_info *pg_info,
			size_t size, int is_zone)
{
	t_list	*prev;

	if (!head)
		return (0);
	if (is_zone && find_size_in_pg_alloc(pg_info, size, &prev))
		return (mem_alloc_init(prev, pg_info, size));
	if (is_zone)
		return (0);
	if (find_size_w_next_page(*head, size, &prev) == 1)
		return (mem_alloc_init(prev, pg_info, size));
	prev = new_page_alloc(head, size + sizeof(t_list));
	if (!prev)
		return (0);
	pg_info = (t_page_info *)(prev->content);
	return (mem_alloc_init(0, pg_info, size));
}
