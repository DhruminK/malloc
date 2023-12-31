/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:49:43 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/08 18:19:51 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_FUNC_H
# define HELPER_FUNC_H

# include <unistd.h>
# include <inttypes.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	size_t			size;
	struct s_list	*next;
}					t_list;

void				ft_lst_add_front(t_list **head, t_list *ele);
void				ft_lst_add_back(t_list **head, t_list *ele);
void				ft_lst_add_before(t_list **head, t_list *ele,
						void *ref, int (*f)(void *, void *));
void				ft_lst_add_after(t_list **head, t_list *ele,
						void *ref, int (*f)(void *, void *));
t_list				*ft_lst_remove_front(t_list **head);
t_list				*ft_lst_remove(t_list **head, void *ref,
						int (*f)(void *, void *));
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(long n, int fd);
void				ft_puthex_fd(size_t n, int fd, int is_prefix);
void				ft_putunbr_fd(size_t n, int fd);

#endif
