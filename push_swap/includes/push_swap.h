/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdexmun <thdexmun@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 11:00:03 by johiew            #+#    #+#             */
/*   Updated: 2026/08/27 15:07:33 by thdexmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "libftprintf.h"
# include <stdbool.h>

typedef struct s_bucket_vars
{
	int				smallest;
	int				range;
	unsigned int	bucket_volume;
	int				bucket_size;
	int				index;
	int				index_back;
	int				*bucket_ranges;
	t_list			*stack_b_top;
}					t_bucket_vars;

typedef struct s_setsteps_vars
{
	unsigned int	stepa;
	unsigned int	stepb;
	unsigned int	stack_size;
	unsigned int	stackb_size;
	int				set;
}					t_setsteps_vars;

typedef enum e_op_stack
{
	NOSTACK = 0,
	A = 1,
	B = 2,
	BOTH = 3
}			t_op_stack;

typedef enum e_op_print
{
	PRINT = 1,
	NOPRINT = 0
}			t_op_print;

typedef enum e_op_count
{
	COUNT = 1,
	NOCOUNT = 0
}			t_op_count;

typedef enum e_op_mode
{
	NONE = 0,
	SIMPLE = 1,
	MEDIUM = 2,
	COMPLEX = 3,
	ADAPTIVE = 4
}			t_op_mode;

typedef struct s_op_params
{
	t_op_stack	stack;
	t_op_print	print;
	t_op_count	count;
}				t_op_params;

typedef struct s_operations
{
	unsigned int	total;
	unsigned int	sa;
	unsigned int	sb;
	unsigned int	ss;
	unsigned int	pa;
	unsigned int	pb;
	unsigned int	ra;
	unsigned int	rb;
	unsigned int	rr;
	unsigned int	rra;
	unsigned int	rrb;
	unsigned int	rrr;
}	t_operations;

typedef struct s_parsing
{
	t_list			*tmp;
	t_list			*tmp2;
	t_list			*lst;
	t_list			*new_node;
	int				index;
	int				value;
	unsigned int	total;
	t_operations	op_counter;
	t_op_params		op_params;
	t_op_mode		mode;
	unsigned int	bench;
}	t_parsing;

void		free_split(char **split);
void		free_lst(void *lst);
int			is_valid_num(char *input);
long long	ft_atoll(const char *nptr);
int			ft_checkargc(int argc);
char		*ft_joinargv(char **argv);
int			check_valid_conlst(t_parsing *va, char **list_str);
int			check_dup(t_parsing *va);
int			all_check(t_parsing *va, char **argv);
double		compute_disorder(t_list **stack);
void		print_sort(t_parsing *va);
void		bucket_sort(t_list **stack, t_parsing *parsing);
void		bucket_insertion_sort(t_list **stack, t_list **stack_b,
				t_bucket_vars *props, t_parsing *parsing);
void		insertion(t_parsing *va);
void		insertion_alt(t_parsing *va);
void		insertion_alt2(t_parsing *va);
void		insertion_simple(t_parsing *va);
void		insertion_simple2(t_parsing *va);
void		radix(t_parsing *va);
void		radix_binary(t_parsing *va);
void		radix_mix(t_parsing *va);
void		insertion_simple(t_parsing *va);
char		*check_mode(t_parsing *va, char *str);
void		chunk_sort(t_parsing *va);
void		convert_to_ranks(t_list *lst);
void		insert_smart_descending(t_list **a, t_list **b, t_parsing *va);
int			check_cost_descending(t_list *b, int target);
int			check_cost_ascending(t_list *b, int target);
void		insert_smart_ascending(t_list **a, t_list **b, t_parsing *va);
void		benchmark(t_operations *op_counter,
				double disorder, unsigned int mode);
int			checker_swap(t_list **a, t_list **b, t_parsing *va, char *op);
int			checker_rotate(t_list **a, t_list **b, t_parsing *va, char *op);
int			checker_rrotate(t_list **a, t_list **b, t_parsing *va, char *op);
int			checker_push(t_list **a, t_list **b, t_parsing *va, char *op);
void		checker_op_error_clear(t_list **a, t_list **b, char *op);
int			checker(t_list **a, t_list **b, t_parsing *va);
void		simple(t_parsing *va);
void		sort_five(t_parsing *va);
void		sort_three(t_parsing *va);

#endif