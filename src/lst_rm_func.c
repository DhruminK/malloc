/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_rm_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:59:32 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 11:04:10 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper_func.h"

t_list	*ft_lst_remove_front(t_list **head)
{
	t_list	*ele;

	if (!head || !*head)
		return (0);
	ele = *head;
	*head = (*head)->next;
	ele->next = 0;
	return (ele);
}

t_list	*ft_lst_remove(t_list **head, void *ref, int (*f)(void *, void *))
{
	t_list	*ele;
	t_list	*p;

	if (!head || !*head)
		return (0);
	if (!f || !f((*head)->content, ref))
		return (ft_lst_remove_front(head));
	p = (*head);
	ele = p->next;
	while (ele)
	{
		if (!f(ele->content, ref))
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
