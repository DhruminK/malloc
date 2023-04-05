/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:53:14 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 10:59:09 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper_func.h"

void	ft_lst_add_front(t_list **head, t_list *ele)
{
	if (!head || !ele)
		return ;
	ele->next = *head;
	*head = ele;
}

void	ft_lst_add_back(t_list **head, t_list *ele)
{
	t_list	*e;

	if (!head || !ele)
		return ;
	if (!*head)
	{
		*head = ele;
		return ;
	}
	e = *head;
	while (e->next)
		e = e->next;
	e->next = ele;
}

void	ft_lst_add_before(t_list **head, t_list *ele,
			void *ref, int (*f)(void *, void *))
{
	t_list	*prev;
	t_list	*e;

	if (!head || !ele)
		return ;
	if (!*head || !(f((*head)->content, ref)))
		return (ft_lst_add_front(head, ele));
	prev = *head;
	e = prev->next;
	while (e)
	{
		if (!(f(e->content, ref)))
			return (ft_lst_add_front(&(prev->next), ele));
		prev = e;
		e = e->next;
	}
	prev->next = ele;
}

void	ft_lst_add_after(t_list **head, t_list *ele,
			void *ref, int (*f)(void *, void *))
{
	t_list	*e;

	if (!head || !ele)
		return ;
	if (!*head)
		return (ft_lst_add_front(head, ele));
	e = *head;
	while (e->next)
	{
		if (!(f(e->content, ref)))
			return (ft_lst_add_front(&(e->next), ele));
		e = e->next;
	}
	e->next = ele;
}
