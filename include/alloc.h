/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:40:34 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 20:30:32 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "helper_func.h"
# include <sys/mman.h>

# define TZ_SIZE	10
# define SZ_SIZE	20

# define TZ_MAX		2
# define SZ_MAX		4

# define PG_MARGIN	40

typedef struct s_page_info
{
	void			*page_start;
	void			*page_end;
	void			*alloc_start;
	t_list			*alloc;
}					t_page_info;

typedef struct s_gen_info
{
	int				is_tiny_alloc;
	int				is_small_alloc;
	t_page_info		tiny;
	t_page_info		small;
	t_list			*large;
	size_t			pg_size;
}					t_gen_info;

extern t_gen_info	g_gen_info;

int					zone_init(void);
int					find_size_in_pg_alloc(t_page_info *pg_info,
						size_t size, t_list **prev);
int					find_size_w_next_page(t_list *pg,
						size_t size, t_list **prev);
int					find_alloc_in_page(t_page_info *pg_info,
						void *addr, t_list **alloc);
int					find_alloc_multi_page(t_list *p, void *addr,
						t_list **pg, t_list **alloc);

void				size_to_pg(size_t *s, size_t pg_size, int ceil);
void				*mmap_alloc(void *addr, size_t *size);
int					check_zone_alloc(void *addr, size_t size);
t_list				*new_page_alloc(t_list **head, size_t size);
int					new_zone_alloc(size_t size, t_page_info *pg_info);
int					page_end_alloc(t_list *pg, size_t size);
void				page_dealloc(t_list *pg, t_list *prev);
void				ft_page_div(t_list *pg, t_list *alloc,
						void *addr, size_t size);

int					ft_lst_merge_page_after(t_list *pg);
void				ft_lst_add_page_to_lst(t_list **head,
						void **addr, t_list *ele);
t_list				*ft_lst_init_new_pg(void *addr, size_t size);
void				*mem_alloc_init(t_list *prev,
						t_page_info *pg_info, size_t size);
void				*mem_alloc(t_list **head, t_page_info *pg_info,
						size_t size, int is_zone);
int					ft_mem_dealloc(t_list *pg, t_list *alloc);
int					ft_zone_mem_dealloc(t_page_info *pg_info, t_list *alloc);

void				show_alloc_mem(void);
void				*malloc(size_t size);
#endif
