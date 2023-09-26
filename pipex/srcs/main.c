/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:22:23 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/26 22:01:58 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

//parse
// < : exec last one
// << : exec everything
// > : make all files for >, but the text inside is only in last one
// >> : make all files for >>, but the text inside is only in last one

// ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
// < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// ./pipex here_doc LIMITER cmd1 cmd2 cmd3 file
// cmd << LIMITER | cmd1 >> file


void	init_bundle(t_bundle *bundle, int argc, char *argv[])
{
	bundle->filename = argv[1];
	bundle->first_cmd_idx = 2;
	bundle->cmd_cnts = argc - 1 - bundle->first_cmd_idx;
	bundle->outfile_flag = O_WRONLY | O_CREAT | O_TRUNC;
	bundle->parsed_path = NULL;
	bundle->cmd_args = NULL;
}

void	write_to_temp_file(int temp_file_fd, char *argv[])
{
	char	*gnl_ret;
	while (1)
	{
		gnl_ret = get_next_line(STDIN_FILENO);
		if (!gnl_ret)
		{
			ft_printf("Gnl Error\n");
			exit(1014);//exit code
		}
		if (ft_strlen(argv[2]) + 1 == ft_strlen(gnl_ret)
			&& ft_strncmp(argv[2], gnl_ret, ft_strlen(argv[2])) == 0
			&& gnl_ret[ft_strlen(argv[2])] == '\n')
			{
				free(gnl_ret);
				break ;
			}
		if (write(temp_file_fd, gnl_ret, ft_strlen(gnl_ret)) == -1)
			ft_error("Write tmp file Error ", 1014);//exit code
		free(gnl_ret);
	}
}

void	check_here_doc(t_bundle *bundle, char *argv[])
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		int		temp_file_fd;

		bundle->outfile_flag = O_WRONLY | O_CREAT | O_APPEND;
		bundle->filename = ft_strdup("tmp");
		if (!bundle->filename)
			ft_error("Malloc Error ", 1014);//exit code
		while (!access(bundle->filename, F_OK))
		{
			size_t sz = ft_strlen(bundle->filename);
			bundle->filename = ft_realloc(sz, bundle->filename, sz + 3 + 1);
			ft_strlcat(bundle->filename, "tmp", sz + 3 + 1);
		}
		temp_file_fd = open(bundle->filename, O_RDWR | O_CREAT, 0644);
		if (temp_file_fd == -1)
			ft_error("Open Error ", 1014);//exit code
		write_to_temp_file(temp_file_fd, argv);
		close(temp_file_fd);
		bundle->first_cmd_idx++;
		bundle->cmd_cnts--;
	}
}



void	parse_cmds(t_bundle *bundle, char *argv[])
{
	int	idx;

	bundle->cmd_args = (char ***)malloc(sizeof(char **) * (bundle->cmd_cnts + 1));
	if (!bundle->cmd_args)
	{
		ft_printf("Malloc Error\n");
		exit(1014); //exit code
	}
	bundle->cmd_args[bundle->cmd_cnts] = NULL;
	idx = -1;
	while (++idx < bundle->cmd_cnts)
	{
		bundle->cmd_args[idx] = ft_split(argv[bundle->first_cmd_idx + idx] ,' ');
		if (!bundle->cmd_args[idx])
		{
			ft_printf("Split Error1\n");
			exit(1014); //exit code
		}
	}
}



void	parse_path(t_bundle *bundle, char *envp[])
{
	char *envp_path;
	int	idx = -1;

	while (envp[++idx])
	{
		if (ft_strncmp("PATH=", envp[idx], 5) == 0)
		{
			envp_path = ft_strchr(envp[idx], '=') + 1;
			bundle->parsed_path = ft_split(envp_path, ':');
			if (!bundle->parsed_path)
			{
				ft_printf("Split Error2\n");
				exit(1014);//exit code
			}
			break ;
		}
	}
}

void	exec_one_cmd(t_bundle *bundle, int argc, char *argv[], char *envp[])
{
	int infile_fd;
	int outfile_fd;
	int path_idx;
	char *path_plus_cmd;
	
	infile_fd = open(bundle->filename, O_RDONLY);
	if (infile_fd == -1)
		ft_error("Open Error ", 1014);//exit code
	outfile_fd = open(argv[argc - 1], bundle->outfile_flag, 0644);
	if (outfile_fd == -1)
		ft_error("Open Error ", 1014);//exit code
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error("Dup2 Error ", 1014);//exit code
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error("Dup2 Error ", 1014);//exit code
	close(infile_fd);
	close(outfile_fd);
	
	execve(bundle->cmd_args[0][0], bundle->cmd_args[0], envp);
	path_idx = -1;
	while (bundle->parsed_path[++path_idx])
	{
		path_plus_cmd = ft_strjoin(bundle->parsed_path[path_idx], "/");
		path_plus_cmd = ft_strjoin(path_plus_cmd, bundle->cmd_args[0][0]);
		execve(path_plus_cmd, bundle->cmd_args[0], envp);
	}
	ft_error("Cmd not found Error ", 1014);//exit code
}

void	exec_multiple_cmds(t_bundle *bundle, int argc, char *argv[], char *envp[])
{
	int	idx;
	int	fd[2];
	int	before_fd_read;
	int	pid;

	idx = -1;
	while (++idx < bundle->cmd_cnts)
	{
		//if (before_fdread)
		//	closer(before_fdread)
		before_fd_read = fd[0];
		if (pipe(fd) == -1)
			ft_error("Pipe Error ", 1014);//exit_code
		pid = fork();
		if (pid < 0)
			ft_error("Fork Error ", 1014);//exit_code
		if (pid == 0)
		{
			// Child process

			if (idx == 0) //first child process
			{
				close(fd[0]);
				int	infile_fd;

				infile_fd = open(bundle->filename, O_RDONLY);
				if (infile_fd == -1)
					ft_error("Open Error ", 1014);//exit code
				if (dup2(infile_fd, STDIN_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				close(fd[1]);
				close(infile_fd);
			}
			else if (idx == bundle->cmd_cnts - 1) // last child process
			{
				int	outfile_fd;

				close(fd[0]);
				close(fd[1]);
				outfile_fd = open(argv[argc - 1], bundle->outfile_flag, 0644);
				if (outfile_fd == -1)
					ft_error("Open Error ", 1014);//exit code
				if (dup2(before_fd_read, STDIN_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				if (dup2(outfile_fd, STDOUT_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				close(before_fd_read);
				close(outfile_fd);
			}
			else //mid child process
			{
				close(fd[0]);
				if (dup2(before_fd_read, STDIN_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				close(before_fd_read);
				close(fd[1]);
			}
			execve(bundle->cmd_args[idx][0], bundle->cmd_args[idx], envp);
			int path_idx = -1;
			while (bundle->parsed_path[++path_idx])
			{
				char *path_plus_cmd = ft_strjoin(bundle->parsed_path[path_idx], "/");
				path_plus_cmd = ft_strjoin(path_plus_cmd, bundle->cmd_args[idx][0]);
				execve(path_plus_cmd, bundle->cmd_args[idx], envp);
			}
			ft_error("Cmd not found Error ", 1014);//exit code
		}
		close(fd[1]);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_bundle	bundle;
	int			idx;

	if (argc < 4)
	{
		ft_printf("Not Enought args\n");
		return (0);
	}
	init_bundle(&bundle, argc, argv);
	check_here_doc(&bundle, argv);
	parse_cmds(&bundle, argv);
	parse_path(&bundle, envp);
	if (bundle.first_cmd_idx == argc - 2)
		exec_one_cmd(&bundle, argc, argv, envp);
	else
		exec_multiple_cmds(&bundle, argc, argv, envp);

	idx = -1;
	while (++idx < bundle.cmd_cnts)
		if (wait(0) == -1)
			ft_error("Wait Error ", 1014);//exit code
	//TODO :: rm tmp file
	return (0);
}
