#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define ERROR "Error\n"
# define ASCEND 9999
# define DESCEND -9999
# define SIZEONE 8888

#include "../libft/libft.h"

typedef struct	s_dll
{
	int				value;
	struct s_dll	*next;
	struct s_dll	*prev;
}				t_dll;

typedef struct	s_sort_type
{
	int					chunk_size;
	int					type;
	struct s_sort_type	*next;
	struct s_sort_type	*prev;
}				t_st;


void	check_dup(int **arr, int inp, int arr_idx);
int		*parse_input(int argc, char **argv);
t_dll	*make_nodes(int val);
void	make_stacks(int inp_num, t_dll **head_a, t_dll **head_b, int *inp_list);
void	make_empty_stack(t_dll **head_b, int inp_num);
void	make_filled_stack(t_dll **head_a, int *inp_list, int inp_num);
t_st	*make_inform_stack(int inp_num, int *inp_list);
void	append_node(t_st **head, int chunk_size);
int		check_des_asc(int *idx, int inp_num, int *inp_list, int *chunk_size);


#endif