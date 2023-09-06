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
void		ft_chunk_push(t_stacks *stacks, int cmd, int reverse_flag);
void		ft_rotate(t_stacks *stacks, int cmd);
void		ft_chunk_rotate(t_stacks *stacks, int cmd);
void		hard_sort(int *inp_list, int inp_list_size, t_stacks *stks, t_dll *stk);
void		sort_2args(t_dll *stk);
void		sort_3args(t_dll *stk);
void		sort_4args(int *inp_list, int inp_list_size, t_stacks *stks);
void		sort_5args(int *inp_list, int inp_list_size, t_stacks *stks);
void		sort_ascend(int *inp_list, int inp_list_size, int *arr);
void		first_move_to_b(t_stacks *stks, int first_b_num, int *sorted_order);
void		set_chunk_node(t_chunk_dll *new_node, int chunk_size);
void		insert_remainder(t_stacks *stks);
int			count_remainder(t_stacks *stks);
void		pb_remainder(t_stacks *stks);

void	merge_to_a(t_stacks *stks, int size, int type);
void	merge_to_b(t_stacks *stks, int size, int type);
void	finally_merge_to_b(t_stacks *stks, int *size, int type);
void	finally_merge_to_a(t_stacks *stks, int *size, int type);
void	move_chunk_to_a_bottom(t_stacks *stks, int size);
void	move_chunk_to_a_top(t_stacks *stks, int size);
void	move_chunk_to_b_bottom(t_stacks *stks, int size);
void	move_chunk_to_b_top(t_stacks *stks, int size);
int		is_sorted(t_dll *stk, int size, int type);




void	print_stcks(t_stacks stks); /////////////////////////////
void	print_chunk_stcks(t_stacks stks); //////////////////




#endif