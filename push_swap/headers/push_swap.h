#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define ERROR "Error\n"
# define ASCEND 1
# define DESCEND -1
# define SA 1
# define SB 2
# define SS 3
# define PA -50
# define PB 50
# define RA 30
# define RB 40
# define RR 70
# define RRA -30
# define RRB -40
# define RRR -70

# define CSA 9999
# define CSB 9998
# define CPA 9997
# define CPB 9996
# define CRA 9995
# define CRB 9994
# define CRRA 9993
# define CRRB 9992


#include <stdio.h>//////////////////
#include "../libft/libft.h"

typedef struct	s_dll
{
	int				value;
	struct s_dll	*next;
	struct s_dll	*prev;
}				t_dll;

typedef struct	s_chunk_dll
{
	int					chunk_size;
	int					type;
	struct s_chunk_dll	*next;
	struct s_chunk_dll	*prev;
}				t_chunk_dll;

typedef struct	s_stacks
{
	t_dll		*stk_a;
	t_dll		*stk_b;
	t_chunk_dll	*chunk_stk_a;
	t_chunk_dll	*chunk_stk_b;
	int			initial_chunk_stk_size;
	t_list		*cmd_list;
}				t_stacks;

void		check_dup(int **arr, int inp, int arr_idx);
int			*parse_input(int argc, char **argv, int *ret_size);
void		free_split_ret(char **split_ret);
int			ft_ps_atoi(const char *str, int *atoi_flag);
t_dll		*make_nodes(int val);
void		make_stacks(t_stacks *stacks, int inp_num, int *inp_list);
void		make_stack_b(t_dll **stk_b, int inp_num);
t_dll		*make_stack_a(int *inp_list, int inp_num);
t_chunk_dll	*make_chunk_stack_a(int inp_num, int *inp_list, t_stacks *stacks);
t_chunk_dll	*make_chunk_stack_b(int size);
void		append_node(t_chunk_dll **head, int chunk_size);
int			check_des_asc(int *idx, int inp_num, int *inp_list, int *chunk_size);
void		merge(int argc, int *inp_list);
int			get_triangle_nums(int total_size);
int			ft_pow(int base, int exponent);
t_dll		*pop(t_dll **stk);
t_chunk_dll	*cpop(t_chunk_dll **stk);
void		push(t_dll *node, t_dll **stk);
void		cpush(t_chunk_dll *node, t_chunk_dll **stk);
void 		ft_swap(t_stacks *stacks, int cmd);
void		ft_chunk_swap(t_stacks *stacks, int cmd);
void		ft_push(t_stacks *stacks, int cmd);
void		ft_chunk_push(t_stacks *stacks, int cmd);
void		ft_rotate(t_stacks *stacks, int cmd);
void		ft_chunk_rotate(t_stacks *stacks, int cmd);




#endif