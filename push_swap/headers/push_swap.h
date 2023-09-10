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



#include "../libft/libft.h"


void		check_dup(int *arr, int inp, int arr_idx);
int			*parse_input(int argc, char **argv, int *ret_size);
void		free_split_ret(char **split_ret);
int			ft_ps_atoi(const char *str);
void		make_stacks(t_stacks *stacks, int inp_num, int *inp_list);
t_dll		*make_stack_a(int *inp_list, int inp_num);
t_dll		*pop(t_dll **stk);
void		push(t_dll *node, t_dll **stk);
void 		ft_swap(t_stacks *stacks, int cmd);
void		ft_push(t_stacks *stacks, int cmd);
void		ft_rotate(t_stacks *stacks, int cmd);
void		hard_sort(int *inp_list, int inp_list_size, t_stacks *stks, t_dll *stk);
void		sort_2args(t_dll *stk);
void		sort_3args(t_dll *stk);
void		sort_4args(int *inp_list, int inp_list_size, t_stacks *stks);
void		sort_5args(int *inp_list, int inp_list_size, t_stacks *stks);
void		sort_ascend(int *inp_list, int inp_list_size, int *arr);

void	merge_to_a(t_stacks *stks, int size, int type);
void	merge_to_b(t_stacks *stks, int size, int type);
void	finally_merge_to_b(t_stacks *stks, int *size, int type);
void	finally_merge_to_a(t_stacks *stks, int *size, int type);
void	move_chunk_to_a_bottom(t_stacks *stks, int size);
void	move_chunk_to_a_top(t_stacks *stks, int size);
void	move_chunk_to_b_bottom(t_stacks *stks, int size);
void	move_chunk_to_b_top(t_stacks *stks, int size);
int		is_sorted(t_dll *stk, int size, int type);
void	print_content(t_list *temp);
void	print_result(t_stacks *stks);
void	optimize_cmds(t_stacks *stks, int *flag);
void	merge_cmd(t_list *cmd_node, int cmd, int *flag);


long long	update_a_bottom_value(t_stacks *stks, int chunk_size, int type);
long long	update_b_top_value(t_stacks *stks, int chunk_size, int type);
long long	update_b_bottom_value(t_stacks *stks, int chunk_size, int type);
long long	out_of_comparison(int type);
void		chunks_to_a(t_stacks *stks, long long *values, int *size, int type);
void		chunks_to_a_descend(t_stacks *stks, long long *values, int *size);
void		chunks_to_a_ascend(t_stacks *stks, long long *values, int *size);
long long	update_a_bottom_value(t_stacks *stks, int chunk_size, int type);
long long	update_b_bottom_value(t_stacks *stks, int chunk_size, int type);
long long	out_of_comparison(int type);
void		chunks_to_b(t_stacks *stks, long long *values, int *size, int type);
void	    chunks_to_b_ascend(t_stacks *stks, long long *values, int *size);
void		chunks_to_b_descend(t_stacks *stks, long long *values, int *size);
void	clear_stacks(t_stacks *stks, int *inp_list);
void	ft_stackclear(t_dll *stk);


#endif