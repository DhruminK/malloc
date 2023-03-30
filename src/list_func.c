/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:28:39 by dkhatri           #+#    #+#             */
/*   Updated: 2023/03/29 15:11:43 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	ft_lst_add_back(t_list **list, t_list *ele)
{
	t_list	*e;

	if (!list || !ele)
		return ;
	if (!*list)
	{
		*list = ele;
		return ;
	}
	e = *list;
	while (e->next)
		e = e->next;
	e->next = ele;
}

void	ft_lst_add_front(t_list **list, t_list *ele)
{
	if (!list || !ele)
		return ;
	ele->next = *list;
	*list = ele;
}

t_list	*ft_lst_remove_front(t_list **list)
{
	t_list	*ele;

	if (!list || !*list)
		return (0);
	ele = *list;
	*list = ele->next;
	ele->next = 0;
	return (ele);
}

t_list	*ft_lst_remove(t_list **list, void *ref, int (*f)(void *, void *))
{
	t_list	*ele;
	t_list	*p;

	if (!list || !*list || !f)
		return (0);
	ele = *list;
	if (f(ele->content, ref) == 0)
		return (ft_lst_remove_front(list));
	p = ele;
	ele = ele->next;
	while (ele)
	{
		if (f(ele->content, ref) == 0)
		{
			p->next = ele->next;
			ele->next = 0;
			return (ele);
		}
		p = ele;
		ele = ele->next;
	}
	return (0);
}
