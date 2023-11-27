/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:07:20 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/20 15:00:04 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	g_exit_status;

int	exec_builtin(char *cmd_name, char **cmd_argv, t_bundle *bundle)
{
	if (ft_strlen(cmd_name) == 4 && !ft_strcmp(cmd_name, "echo"))
		return (echo(cmd_argv));
	if (ft_strlen(cmd_name) == 2 && !ft_strcmp(cmd_name, "cd"))
		return (cd(bundle, cmd_argv));
	if (ft_strlen(cmd_name) == 3 && !ft_strcmp(cmd_name, "pwd"))
		return (pwd());
	if (ft_strlen(cmd_name) == 6 && !ft_strcmp(cmd_name, "export"))
		return (export(bundle, cmd_argv));
	if (ft_strlen(cmd_name) == 5 && !ft_strcmp(cmd_name, "unset"))
		return (unset(bundle, cmd_argv));
	if (ft_strlen(cmd_name) == 3 && !ft_strcmp(cmd_name, "env"))
		return (env(bundle));
	if (ft_strlen(cmd_name) == 4 && !ft_strcmp(cmd_name, "exit"))
		ft_exit(cmd_argv, -1);
	return (1);
}

t_pipe	*parsing(t_bundle *bundle, char *rl)
{
	t_token	*token_head;
	t_token	*temp;
	t_pipe	*root;
	t_token	*make_tree_tmp;

	token_head = tokenize(rl);
	temp = syntax_analyze(token_head);
	if (!temp)
		return (NULL);
	expansion_main(token_head, bundle);
	make_tree_tmp = token_head->next;
	root = make_tree(bundle, make_tree_tmp);
	free_token(token_head);
	return (root);
}

int	check_file_exist(t_redirect_s *redirect_s)
{
	if (redirect_s && redirect_s->redirect && redirect_s->redirect->filename)
	{
		if (access(redirect_s->redirect->filename, F_OK))
		{
			write(2, redirect_s->redirect->filename,
				ft_strlen(redirect_s->redirect->filename));
			write(2, ": No such file or directory\n", 28);
			return (-1);
		}
	}
	if (redirect_s->redirect_s)
		if (check_file_exist(redirect_s->redirect_s) == -1)
			return (-1);
	return (0);
}

int	exec_one_builtin(t_bundle *bundle, t_pipe *root)
{
	int			before_stdin;
	int			before_stdout;

	if (root->cmd->redirect_s)
	{
		before_stdin = dup(STDIN_FILENO);
		before_stdout = dup(STDOUT_FILENO);
		if (pre_exec_here_doc(root, bundle) == -1)
		{
			reset_base_fd(before_stdin, before_stdout);
			return (-1);
		}
		if (exec_redirect_s_recur(root->cmd->redirect_s, bundle) == -1)
		{
			if (root->cmd->redirect_s)
				reset_base_fd(before_stdin, before_stdout);
			return (-1);
		}
	}
	g_exit_status = exec_builtin(root->cmd->simple_cmd->cmd_path,
			root->cmd->simple_cmd->cmd_argv, bundle);
	if (root->cmd->redirect_s)
		reset_base_fd(before_stdin, before_stdout);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*inp;
	t_pipe		*root;
	t_bundle	bundle;

	setting(argc, argv, &bundle, envp);
	while (1)
	{
		init_bundle(&bundle);
		inp = readline("ϞϞ(๑⚈ ․̫ ⚈๑) > ");
		if (!inp)
			ctrl_d_handler();
		if (!*inp)
		{
			free(inp);
			continue ;
		}
		add_history(inp);
		root = parsing(&bundle, inp);
		free(inp);
		if (exec_tree(&bundle, root) == -1)
			continue ;
		free_hrdc_nodes(&bundle);
		free_tree(root);
	}
	return (free_bundle(&bundle));
}
