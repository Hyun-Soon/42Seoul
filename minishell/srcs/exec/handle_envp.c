/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:48:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 22:26:47 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**get_path(char **envp)
{
	int		idx;
	char	**temp_split;
	char	**splited_path;

	idx = -1;
	while (envp[++idx])
		if (ft_strlen(envp[idx]) >= 5 && ft_strncmp(envp[idx], "PATH=", 5) == 0)
			break ;
	if (!envp[idx])
		return (NULL);
	temp_split = ft_split(envp[idx], '=');
	if (!temp_split)
		ft_error(MALLOC_ERRMSG, 1);
	splited_path = ft_split(temp_split[1], ':');
	free_2d_malloced_str(temp_split);
	if (!splited_path)
		ft_error(MALLOC_ERRMSG, 1);
	return (splited_path);
}

char	*getenv_minishell(t_bundle *bundle, char *var_name)
{
	int		idx;
	size_t	var_len;

	idx = -1;
	var_len = ft_strlen(var_name);
	while (bundle->envp[++idx])
		if (ft_strlen(bundle->envp[idx]) >= var_len
			&& ft_strncmp(bundle->envp[idx], var_name, var_len) == 0)
			break ;
	return (bundle->envp[idx]);
}

char	*get_var_name(char *str)
{
	int		idx;
	char	*var_name;

	idx = -1;
	while (str[++idx] != '=')
		;
	var_name = ft_substr(str, 0, idx);
	return (var_name);
}

int	exist_already(t_bundle *bundle, char *new_str)
{
	int		idx;
	char	*var_name;
	size_t	var_name_len;

	idx = -1;
	var_name = get_var_name(new_str);
	var_name_len = ft_strlen(var_name);
	while (bundle->envp[++idx])
		if (ft_strlen(bundle->envp[idx]) > var_name_len
			&& ft_strncmp(bundle->envp[idx], var_name, var_name_len) == 0)
			break ;
	free(var_name);
	if (bundle->envp[idx] == NULL)
		return (-1);
	free(bundle->envp[idx]);
	bundle->envp[idx] = ft_strdup(new_str);
	return (idx);
}

void	append_new_env_var(t_bundle *bundle, int ret_envp_idx, char *new_str)
{
	char	**ret_envp;

	if (!ft_strchr(new_str, '='))
		return ;
	if (exist_already(bundle, new_str) != -1)
		return ;
	ret_envp = (char **)malloc(sizeof(char *) * (bundle->envp_len + 2));
	if (!ret_envp)
		ft_error(MALLOC_ERRMSG, 1);
	ret_envp[bundle->envp_len + 1] = NULL;
	while (++ret_envp_idx < bundle->envp_len)
		ret_envp[ret_envp_idx] = bundle->envp[ret_envp_idx];
	ret_envp[ret_envp_idx] = ft_strdup(new_str);
	if (!ret_envp[ret_envp_idx])
		ft_error(MALLOC_ERRMSG, 1);
	free(bundle->envp);
	bundle->envp = ret_envp;
	bundle->envp_len++;
}
