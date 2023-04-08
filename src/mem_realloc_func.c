/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_realloc_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:26:27 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/08 18:20:14 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*mem_realloc_end_func(t_list *pg, t_list *alloc, size_t size)
{
	t_page_info	*pg_info;
	size_t		len;

	if (!pg || !alloc)
		return (0);
	pg_info = (t_page_info *)(pg->content);
	if (alloc->next)
		return (mem_realloc_in_page(pg_info, alloc, size));
	if (pg_info->page_end - (size_t)(alloc->content) >= size)
	{
		alloc->size = size;
		return (alloc->content);
	}
	if (pg->next && ((size_t)(pg->next) - (size_t)(alloc->content)) < size)
		return (0);
	len = size - (pg_info->page_end - (size_t)(alloc->content));
	if (pg->next && len + pg_info->page_end + PG_MARGIN >= (size_t)(pg->next))
		len = (size_t)pg->next - (pg_info->page_end);
	if (page_end_alloc(pg, len) == -1)
		return (0);
	alloc->size = size;
	return (alloc->content);
}

void	*mem_realloc_in_page(t_page_info *pg_info, t_list *alloc, size_t size)
{
	t_list	*prev;
	size_t	s;
	size_t	l;

	if (!pg_info || !alloc || !(alloc->next))
		return (0);
	prev = (t_list *)pg_info->alloc;
	while (prev && prev->next != alloc)
		prev = prev->next;
	s = (size_t)(prev->content) + prev->size;
	if (!prev)
		s = pg_info->alloc_start;
	if ((size_t)(alloc->next) - s < size)
		return (0);
	s = alloc->size;
	if (s > size)
		s = size;
	alloc->size = size;
	l = (size_t)(alloc->next) - size - sizeof(t_list);
	if (prev)
		prev->next = (t_list *)l;
	else
		pg_info->alloc = l;
	return (ft_memmove((void *)l, alloc, sizeof(t_list) + s));
}

void	*mem_realloc_w_page(t_list *pg, t_list *alloc, size_t size)
{
	t_page_info	*pg_info;

	if (!alloc || alloc->next)
		return (0);
	pg_info = (t_page_info *)(pg->content);
	if (pg_info->alloc != (size_t)alloc)
		return (mem_realloc_end_func(pg, alloc, size));
	if (pg_info->alloc != pg_info->alloc_start)
	{
		alloc = ft_memmove((void *)(pg_info->alloc_start),
				(void *)(pg_info->alloc), sizeof(t_list) + alloc->size);
		pg_info->alloc = (size_t)alloc;
	}
	return (mem_realloc_end_func(pg, alloc, size));
}
