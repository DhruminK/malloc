/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:36:09 by dkhatri           #+#    #+#             */
/*   Updated: 2023/03/30 16:09:37 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	find_size(t_list *a, void *end, t_list **alloc, size_t size)
{
	t_mem_alloc	*al;
	t_mem_alloc	*prev_al;

	if (!a || !alloc)
		return (-1);
	*alloc = a;
	a = a->next;
	while (a)
	{
		al = (t_mem_alloc *)(a->content);
		prev_al = (t_mem_alloc *)((*alloc)->content);
		if ((size_t)(prev_al->end - al->start) >= size)
			return (1);
		*alloc = a;
		a = a->next;
	}
	prev_al = (t_mem_alloc *)((*alloc)->content);
	if ((size_t)(end - (prev_al)->end) >= size)
		return (1);
	return (0);
}

t_list	*ft_init_mem_info(t_list *ele, void *start, size_t size)
{
	t_mem_alloc	a;
	t_mem_alloc	*al;
	t_list		*el;

	if (!ele || !size)
		return (0);
	if (!ele)
		a.start = start;
	else
	{
		al = (t_mem_alloc *)(ele->content);
		a.start = al->end;
	}
	a.end = (void *)size;
	a.data_start = a.start + sizeof(t_mem_alloc) + sizeof(t_list);
	el = a.start;
	el->content = a.start + sizeof(t_list);
	ft_memcpy(el->content, &a, sizeof(t_mem_alloc));
	el->size = sizeof(t_mem_alloc);
	el->next = 0;
	return (el);
}

int	ft_insert_mem_info(t_list *ele, void *start, size_t size, t_list **head)
{
	t_list		*el;

	if (!ele || !head)
		return (-1);
	el = ft_init_mem_info(ele, start, size);
	if (!el)
		return (0);
	if (!ele)
		ft_lst_add_front(head, el);
	else
	{
		el->next = ele->next;
		ele->next = el;
	}
	return (0);
}

void	*zone_mem_alloc(size_t size, t_alloc_info *alloc)
{
	t_list		*al;
	t_mem_alloc	*mem;
	int			b;

	if (!size || !alloc)
		return (0);
	size = size + sizeof(t_mem_alloc) + sizeof(t_list);
	b = 0;
	al = 0;
	if (alloc->alloc)
	{
		mem = (t_mem_alloc *)(alloc->alloc->content);
		if ((size_t)(mem->start - 1 - alloc->start) >= size)
			b = 1;
		if (!b && find_size(alloc->alloc, alloc->end, &al, size) == -1)
			b = 1;
	}
	if ((!b && alloc->alloc) || (ft_insert_mem_info(al,
				alloc->start, size, &(alloc->alloc)) == -1))
		return (0);
	if (!al)
		al = alloc->alloc;
	mem = (t_mem_alloc *)(al->content);
	return (mem->data_start);
}
