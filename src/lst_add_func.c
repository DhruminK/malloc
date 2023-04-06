/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:53:14 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/06 16:52:46 by dkhatri          ###   ########.fr       */
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

void	ft_lst_disp(t_list *ele)
{
	if (!ele)
		return ;
	ft_puthex_fd((size_t)ele, 1, 1);
	ft_putstr_fd("\nCONTENT : ", 1);
	ft_puthex_fd((size_t)(ele->content), 1, 1);
	ft_putstr_fd("\nSIZE : ", 1);
	ft_puthex_fd(ele->size, 1, 1);
	ft_putstr_fd("\nNEXT : ", 1);
	ft_puthex_fd((size_t)(ele->next), 1, 1);
	ft_putstr_fd("\n", 1);
}

# include "alloc.h"

void	ft_pg_disp(t_list *pg)
{
	t_page_info	*pg_info;

	while (pg)
	{
		pg_info = (t_page_info *)(pg->content);
		ft_putstr_fd("PAGE START : ", 1);
		ft_puthex_fd((size_t)(pg_info->page_start), 1, 1);
		ft_putstr_fd(" - ", 1);
		ft_puthex_fd((size_t)(pg_info->page_end), 1, 1);
		/**
		ft_putstr_fd("\nPAGE ALLOC START : ", 1);
		ft_puthex_fd((size_t)(pg_info->alloc_start), 1, 1);
		ft_putstr_fd(" - ", 1);
		ft_puthex_fd((size_t)(pg_info->alloc), 1, 1);
		*/
		ft_putstr_fd("\n", 1);
		pg = pg->next;
	}
}
