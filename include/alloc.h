/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 11:42:31 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 18:35:03 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>
# include "helper_func.h"

# define LARGE_ADDR	0xA0000
# define SMALL_ADDR	0x70000
# define TINY_ADDR	0x50000

# define PG_MARGIN	20

# define SMALL_MAX	80
# define TINY_MAX	40

typedef struct s_alloc_info
{
	void			*start;
	void			*end;
	t_list			*alloc;
	size_t			max;
}					t_alloc_info;

typedef struct s_page_info
{
	void			*page_start;
	void			*page_end;

	void			*alloc_start;
	t_list			*alloc;
}					t_page_info;

typedef struct s_gen_info
{
	int				is_alloc;
	int				pg_size;
	t_page_info		tiny;
	t_page_info		small;
	t_list			*mem;
}					t_gen_info;

extern t_gen_info	g_gen_info;

int					page_alloc_end(t_page_info *pg_info, size_t size);
int					page_alloc_start(void);
int					page_alloc_merge(t_list *pg);
int					new_page_alloc(t_list **pg, void **addr, size_t size);
void				addr_div_pg_size(void **addr, char dir);
int					page_trim_end(t_page_info *pg_info);
int					page_div(t_list *pg, t_list *alloc);
int					page_dealloc_whole_pg(t_list *pg);
int					find_size(size_t size, t_list **pg, t_list **alloc);
void				*ft_mem_alloc_start(t_list *pg, size_t size);
void				*ft_mem_alloc_mid(t_list *prev_alloc, t_list *pg, size_t size);
int					find_alloc(void *addr, t_list **pg, t_list **alloc);
int					find_alloc_in_page(void *addr, t_page_info *pg_info, t_list **alloc);
void				*mem_realloc(t_list *alloc, t_list *pg, size_t size);
void				*mem_alloc_zone(t_list *alloc, t_page_info *pg_info, size_t size);
int					ft_mem_dealloc(t_list *alloc, t_list *pg);
int					ft_mem_dealloc_zone(t_list *alloc, t_page_info *pg_info);
int					gen_info_init(void);
void				*zone_alloc(size_t size, t_page_info *pg_info);
int					zone_dealloc(void *addr, t_page_info *pg_info);
void				*zone_realloc(void *addr, size_t size, int *ret);
int					free_check_zones(void *addr);
void				*large_alloc(size_t size);
int					large_dealloc(void *addr);
void				*large_realloc(void *addr, size_t size, int *ret);
void				ft_str_frerror();
int					alloc_mmap(void *addr, size_t *size);
int					find_realloc_same_ele_pg(t_list *alloc, t_page_info *pg_info, size_t size);
void				*find_realloc(t_list *alloc, t_list *pg, size_t size, int is_zone);
void				*ft_zone_mem_alloc_start(t_page_info *pg_info, size_t size);
void				*ft_zone_mem_alloc_mid(t_list *prev_alloc,
						t_page_info *pg_info, size_t size);
int					find_size_page(size_t size, t_page_info *pg_info, t_list **a);
void				*ft_mem_alloc_init(t_list *prev, void *addr, size_t size);

#endif
