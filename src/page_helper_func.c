/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_helper_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:33:38 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 20:24:43 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	ft_lst_merge_page_after(t_list *pg)
{
	t_page_info	*pg_info;
	t_page_info	*pg_next_info;

	if (!pg || !(pg->next))
		return (0);
	pg_info = (t_page_info *)(pg->content);
	if (pg_info->page_end + PG_MARGIN < (void *)pg->next)
		return (0);
	pg_next_info = (t_page_info *)(pg->next->content);
	pg_info->page_end = pg_next_info->page_end;
	ft_lst_add_back(&(pg_info->alloc), pg_next_info->alloc);
	pg->next = pg->next->next;
	return (1);
}

static int	ft_lst_page_addr_cmp(void *content, void *ref)
{
	t_page_info	*pg_info;

	if (!content || !ref)
		return (1);
	pg_info = (t_page_info *)(content);
	if (pg_info->page_start > ref)
		return (0);
	return (1);
}

void	ft_lst_add_page_to_lst(t_list **head, void **addr, t_list *ele)
{
	t_list	*e;

	*addr = ele;
	if (!head || !ele)
		return ;
	ft_lst_add_before(head, ele, (void *)(ele), &ft_lst_page_addr_cmp);
	ft_lst_merge_page_after(ele);
	e = (*head);
	while (e && e != ele && e->next != ele)
		e = e->next;
	if (e && e != ele && ft_lst_merge_page_after(e) == 1)
		*addr = e;
}

t_list	*ft_lst_init_new_pg(void *addr, size_t size)
{
	t_page_info	*pg_info;
	t_list		*pg;

	if (!addr)
		return (0);
	pg = (t_list *)addr;
	pg->content = (((char *)addr) + sizeof(t_list));
	pg->next = 0;
	pg->size = sizeof(t_page_info);
	pg_info = (t_page_info *)(pg->content);
	pg_info->page_start = addr;
	pg_info->page_end = ((char *)addr) + size;
	pg_info->alloc_start = ((char *)addr)
		+ sizeof(t_list) + sizeof(t_page_info);
	pg_info->alloc = 0;
	return (pg);
}

void	ft_page_div(t_list *pg, t_list *alloc,
			void *addr, size_t size)
{
	t_page_info	*pg_info;
	t_page_info	*ele_pg_i;
	t_list		*ele;
	size_t		len;

	if (!pg || !addr || !size)
		return ;
	if (size < g_gen_info.pg_size)
		return ;
	if (munmap(addr, size) == -1)
		return ;
	pg_info = (t_page_info *)(pg->content);
	len = ((char *)pg_info->page_end - (char *)alloc->next);
	ele = ft_lst_init_new_pg((char *)addr + size, len);
	if (!ele)
		return ;
	ele_pg_i = (t_page_info *)(ele->content);
	ele_pg_i->alloc = alloc->next;
	alloc->next = 0;
	ele->next = pg->next;
	pg->next = ele;
}
