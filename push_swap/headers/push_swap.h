#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define ERROR "Error\n"
# define ASCEND 1
# define DESCEND -1
# define SIZEONE 8888

#include <stdio.h>//////////////////
#include "../libft/libft.h"

typedef struct	s_dll
{
	int				value;
	int				chunk_size;
	int				type;
	struct s_dll	*next;
	struct s_dll	*prev;
}				t_dll;

typedef struct	s_stacks
{
	t_dll	*stk_a;
	t_dll	*stk_b;
	t_dll	*chunk_stk_a;
	t_dll	*chunk_stk_b;
	int		initial_chunk_stk_size;
	t_list	*command;
}				t_stacks;

void	check_dup(int **arr, int inp, int arr_idx);
int		*parse_input(int argc, char **argv, int *ret_size);
void	free_split_ret(char **split_ret);
int		ft_ps_atoi(const char *str, int *atoi_flag);
t_dll	*make_nodes(int val);
void	make_stacks(t_stacks *stacks, int inp_num, int *inp_list);
void	make_stack_b(t_dll **stk_b, int inp_num);
t_dll	*make_stack_a(int *inp_list, int inp_num);
t_dll	*make_chunk_stack_a(int inp_num, int *inp_list, t_stacks *stacks);
t_dll	*make_chunk_stack_b(int size);
void	append_node(t_dll **head, int chunk_size);
int		check_des_asc(int *idx, int inp_num, int *inp_list, int *chunk_size);
void	merge(int argc, int *inp_list);
int		get_triangle_nums(int total_size);


#endif