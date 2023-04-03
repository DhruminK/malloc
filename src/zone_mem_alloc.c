/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_mem_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:24:55 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 18:35:29 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*ft_zone_mem_alloc_start(t_page_info *pg_info, size_t size)
{
	if (!pg_info)
		return (0);
	ft_lst_add_front(&(pg_info->alloc), (t_list *)(pg_info->alloc_start));
	return (ft_mem_alloc_init(0, pg_info->alloc_start, size));
}

void	*ft_zone_mem_alloc_mid(t_list *prev_alloc,
			t_page_info *pg_info, size_t size)
{
	size_t		len;

	if (!prev_alloc || !pg_info)
		return (0);
	len = (size_t)(prev_alloc->content + prev_alloc->size);
	if (prev_alloc->next && (size_t)(prev_alloc->next - len)
			>= size + sizeof(t_list))
		return (ft_mem_alloc_init(prev_alloc, 0, size));
	else if (prev_alloc->next)
		return (0);
	if ((size_t)(pg_info->page_end - len) > size + sizeof(t_list))
		return (ft_mem_alloc_init(prev_alloc, 0, size));
	return (0);
}
