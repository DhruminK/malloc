/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_helper_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:34:13 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/13 12:06:15 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

t_list	*new_pg_ele_init(void *addr, size_t size)
{
	t_list		*ele;
	t_page_info	*pg_info;

	if (!addr || !size)
		return (0);
	ele = (t_list *)(addr);
	ele->content = (addr + sizeof(t_list));
	ele->next = 0;
	ele->size = sizeof(t_page_info);
	pg_info = (t_page_info *)(ele->content);
	pg_info->page_start = (size_t)(addr);
	pg_info->page_end = (pg_info->page_start) + size;
	pg_info->alloc = 0;
	pg_info->alloc_start = (pg_info->page_start
			+ sizeof(t_list) + sizeof(t_page_info));
	return (ele);
}

int	pg_merge_after(t_list *pg)
{
	t_page_info	*pg_info;
	t_page_info	*pg_next_info;

	if (!pg || !(pg->next))
		return (0);
	pg_info = (t_page_info *)(pg->content);
	if ((void *)pg_info->page_end != (void *)(pg->next))
		return (0);
	pg_next_info = (t_page_info *)(pg->next->content);
	ft_lst_add_back((t_list **)&(pg_info->alloc),
		(t_list *)(pg_next_info->alloc));
	pg_info->page_end = pg_next_info->page_end;
	pg->next = pg->next->next;
	return (1);
}

void	pg_add_to_lst_front(t_list **head, t_list *ele, t_list **e)
{
	if (!head || !ele)
		return ;
	ft_lst_add_front(head, ele);
	pg_merge_after(ele);
	*e = ele;
}

void	pg_add_to_lst(t_list **head, t_list *ele, t_list **e)
{
	t_list		*pg;
	t_page_info	*pg_info;

	*e = ele;
	if (!head || !ele || !*head || (*head) > ele)
		return (pg_add_to_lst_front(head, ele, e));
	pg = *head;
	while (pg->next)
	{
		pg_info = (t_page_info *)(pg->content);
		if (pg_info->page_end <= (size_t)(ele) && (pg->next) > ele)
			break ;
		pg = pg->next;
	}
	ele->next = pg->next;
	pg->next = ele;
	if (pg_merge_after(pg) == 1)
	{
		pg_merge_after(pg);
		*e = pg;
	}
	else
		pg_merge_after(ele);
}
