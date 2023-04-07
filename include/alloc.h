/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:40:34 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/07 17:27:09 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "helper_func.h"
# include <pthread.h>
# include <sys/mman.h>
# include <stdint.h>

# define TZ_SIZE	10
# define SZ_SIZE	20

# define TZ_MAX		2
# define SZ_MAX		4

# define PG_MARGIN	40

typedef struct s_page_info
{
	size_t			page_start;
	size_t			page_end;
	size_t			alloc_start;
	size_t			alloc;
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

void				*malloc(size_t size);
void				free(void *addr);
void				show_alloc_mem(void);
void				ft_str_frerror(void *addr);

int					zone_alloc_init(void);
void				*zone_mem_alloc(size_t size, t_page_info *pg_info);
void				*mem_alloc(size_t size);

int					find_size_in_pg(t_page_info *pg_info,
						size_t size, t_list **prev);
int					find_size(t_list *head, size_t size,
						t_list **pg, t_list **alloc);

int					new_zone_alloc(t_page_info *pg_info, size_t size);
int					page_end_alloc(t_list *pg, size_t size);
int					new_page_alloc(t_list **head, size_t size, t_list **e);
int					ft_check_zone_alloc(size_t addr, size_t size);

void				ft_whole_pg_dealloc(t_list *pg);
void				ft_page_dealloc_start(t_list *pg);
void				ft_page_dealloc_start(t_list *pg);
void				ft_page_div(t_list *pg, t_list *prev);

t_list				*new_pg_ele_init(void *addr, size_t size);
int					pg_merge_after(t_list *pg);
void				pg_add_to_lst(t_list **head, t_list *ele, t_list **e);

void				size_to_pg(size_t *len, size_t pg_size, uint8_t ceil);
void				*mmap_alloc(void *addr, size_t size);
int					munmap_dealloc(void *addr, size_t size);

int					zone_mem_dealloc(void *addr, t_page_info *pg_info);
int					mem_dealloc(void *addr);
int					find_addr_in_pg(t_page_info *pgi,
						void *addr, t_list **alloc);
int					find_addr(t_list *head, void *addr,
						t_list **pg, t_list **alloc);
#endif
