/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:22:23 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/25 16:52:10 by hyuim            ###   ########.fr       */
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

int main(int argc, char *argv[], char *envp[])
{
	int	fd[2]; //fd[0] : read , fd[1] : write
	int	pid;
	int	idx;
	char	*filename;
	int	first_cmd_idx;

	first_cmd_idx = 2;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		char	*gnl_ret;
		int		temp_file_fd;

		filename = ft_strdup("tmp");
		if (!filename)
			ft_error("Malloc Error ", 1014);//exit code
		while (!access(filename, F_OK))
		{
			size_t sz = ft_strlen(filename);
			filename = ft_realloc(sz, filename, sz + 3 + 1);
			ft_strlcat(filename, "tmp", sz + 3 + 1);
		}
		temp_file_fd = open(filename, O_RDWR | O_CREAT, 0644);
		if (temp_file_fd == -1)
			ft_error("Open Error ", 1014);//exit code
		while (1)
		{
			gnl_ret = get_next_line(STDIN_FILENO);
			if (!gnl_ret)
				ft_error("Gnl Error ", 1014);//exit code
			if (ft_strlen(argv[2]) + 1 == ft_strlen(gnl_ret)
				&& ft_strncmp(argv[2], gnl_ret, ft_strlen(argv[2])) == 0
				&& gnl_ret[ft_strlen(argv[2])] == '\n')
				break ;
			if (write(temp_file_fd, gnl_ret, ft_strlen(gnl_ret)) == -1)
				ft_error("Write tmp file Error ", 1014);//exit code
		}
		close(temp_file_fd);
		first_cmd_idx++;
	}
	else
		filename = argv[1];


	idx = first_cmd_idx - 1;
	while (++idx < argc - 1)
	{
		int	before_fd_read = fd[0];
		if (pipe(fd) == -1)
			ft_error("Pipe Error ", 1014);//exit_code
		pid = fork();
		if (pid < 0)
			ft_error("Fork Error ", 1014);//exit_code
		if (pid == 0)
		{
			// Child process
			if (idx == first_cmd_idx) //first child process
			{
				close(fd[0]);
				int	infile_fd;

				infile_fd = open(filename, O_RDONLY);
				if (infile_fd == -1)
					ft_error("Open Error ", 1014);//exit code
				if (dup2(infile_fd, STDIN_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				close(fd[1]);
			}
			//else if (idx == argc - 2) // last child process
			//{
			//	int	outfile_fd;

			//	close(fd[0]);
			//	close(fd[1]);
			//	outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
			//	if (outfile_fd == -1)
			//		ft_error("Open Error ", 1014);//exit code
			//	if (dup2(before_fd_read, STDIN_FILENO) == -1)
			//		ft_error("Dup2 Error ", 1014);//exit code
			//	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
			//		ft_error("Dup2 Error ", 1014);//exit code
				
			//}
			else //mid child process
			{
				close(fd[0]);
				if (dup2(before_fd_read, STDIN_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				close(fd[1]);
			}
			char **cmd_args = ft_split(argv[idx], ' ');
			char **envp_path;
			char **split_path;
			int	idx2 = -1;
			while (envp[++idx2])
			{
				if (ft_strncmp("PATH=", envp[idx2], 5) == 0)
				{
					envp_path = ft_split(envp[idx2], '=');
					split_path = ft_split(envp_path[2], ':');
				}
			}
			int	split_path_idx = -1;
			execve(cmd_args[0], cmd_args, envp);
			while (split_path[++split_path_idx])
				execve(ft_strjoin(split_path[split_path_idx], cmd_args[0]), cmd_args, envp);
			ft_error("Cmd not found Error ", 1014);//exit code
		}
	}

	int	outfile_fd;

	
	int idx3 = first_cmd_idx - 1;
	while (++idx3 < argc - 1)
	{
		if (wait(0) == -1)
			ft_error("Waitpid Error ", 1014);//exit code
	}
	close(fd[1]);
	outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT , 0644);
	if (outfile_fd == -1)
		ft_error("Open Error ", 1014);//exit code
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error("Dup2 Error ", 1014);//exit code
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error("Dup2 Error ", 1014);//exit code
	close(fd[0]);
	return (0);
}

//./pipex file1 cmd1 cmd2 cmd3 cmd4 file2
// 1. STDIN을 file1 fd로 dup2한다.
// 2. STDOUT file
// 2. input the text in the file 1 to cmd1
// 3. 