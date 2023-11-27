/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:13:46 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/14 20:16:30 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	print_declare_env(char **str_arr)
{
	int	i;

	i = -1;
	while (str_arr[++i])
	{
		if (write(2, "declare -x ", 11) == -1)
			return (1);
		if (write(STDOUT_FILENO, str_arr[i], ft_strlen(str_arr[i])) == -1)
			return (1);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (1);
	}
	return (0);
}

int	check_exeception(char *inp)
{
	int	idx;

	if (!((inp[0] >= 'a' && inp[0] <= 'z') || (inp[0] >= 'A' && inp[0] <= 'Z')
			|| inp[0] == '_'))
		return (-1);
	idx = -1;
	while (inp[++idx] && inp[idx] != '=')
		if (!((inp[idx] >= 'a' && inp[idx] <= 'z')
				|| (inp[idx] >= 'A' && inp[idx] <= 'Z')
				|| inp[idx] == '_'
				|| (inp[idx] >= '0' && inp[idx] <= '9')))
			return (-1);
	return (0);
}

int	is_in_envp(t_bundle *bundle, char *inp_str)
{
	int		idx;
	size_t	inp_len;

	idx = -1;
	inp_len = ft_strlen(inp_str);
	while (bundle->envp[++idx])
	{
		if (ft_env_var_len(bundle->envp[idx]) == inp_len
			&& !ft_strncmp(bundle->envp[idx], inp_str, inp_len))
			return (idx);
	}
	return (-1);
}

size_t	ft_env_var_len(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx] && s[idx] != '=')
		idx++;
	return (idx);
}

void	rm_inp_env_var(t_bundle *bundle, int found_idx)
{
	char	**ret_envp;
	int		idx;
	int		ret_envp_idx;

	ret_envp = (char **)malloc(sizeof(char *) * (bundle->envp_len));
	if (!ret_envp)
		ft_error(MALLOC_ERRMSG, 1);
	idx = -1;
	ret_envp_idx = -1;
	while (++idx < bundle->envp_len)
	{
		if (idx == found_idx)
			continue ;
		else
			++ret_envp_idx;
		ret_envp[ret_envp_idx] = bundle->envp[idx];
	}
	free(bundle->envp[found_idx]);
	free(bundle->envp);
	bundle->envp = ret_envp;
	bundle->envp_len--;
	bundle->envp[bundle->envp_len] = NULL;
}
