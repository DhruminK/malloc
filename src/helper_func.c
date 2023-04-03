/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:41:57 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 17:39:58 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper_func.h"

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

void	ft_lst_add(t_list **head, void *ref,
		int (*f)(void *, void *), t_list *e)
{
	t_list	*prev;
	t_list	*ele;

	if (!head || !f || !e)
		return ;
	if (!*head || !(f(ref, (*head)->content)))
	{
		ft_lst_add_front(head, e);
		return ;
	}
	prev = *head;
	ele = prev->next;
	while (ele)
	{
		if (!(f(ref, (*head)->content)))
		{
			prev->next = e;
			e->next = ele;
		}
		prev = ele;
		ele = ele->next;
	}
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
