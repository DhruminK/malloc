/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:03:16 by dkhatri           #+#    #+#             */
/*   Updated: 2023/03/30 16:03:17 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_FUNC_H
# define HELPER_FUNC_H

# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	size_t			size;
	struct s_list	*next;
}					t_list;

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_lst_add_back(t_list **list, t_list *ele);
void	ft_lst_add_front(t_list **list, t_list *ele);
t_list	*ft_lst_remove_front(t_list **list);
t_list	*ft_lst_remove(t_list **list, void *ref, int (*f)(void *, void *));

#endif