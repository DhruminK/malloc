/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_dealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:38:39 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 20:28:25 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	ft_mem_dealloc(t_list *pg, t_list *alloc)
{
	t_list		*prev;
	t_page_info	*pg_info;

	if (!pg || !alloc)
		return (-1);
	pg_info = (t_page_info *)(pg->content);
	prev = pg_info->alloc;
	while (prev && prev->next != alloc)
		prev = prev->next;
	if (!prev)
		ft_lst_remove_front(&(pg_info->alloc));
	else
		ft_lst_remove_front(&(prev->next));
	page_dealloc(pg, prev);
	return (0);
}

int	ft_zone_mem_dealloc(t_page_info *pg_info, t_list *alloc)
{
	t_list	*prev;

	if (!pg_info || !alloc)
		return (-1);
	prev = pg_info->alloc;
	while (prev && prev->next != alloc)
		prev = prev->next;
	if (!prev)
		ft_lst_remove_front(&(pg_info->alloc));
	else
		ft_lst_remove_front(&(prev->next));
	return (0);
}
