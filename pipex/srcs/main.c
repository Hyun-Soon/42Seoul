/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:22:23 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/22 20:21:12 by hyuim            ###   ########.fr       */
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

int main(int argc, char *argv[])
{
	int	fd[2];
	int	pid;
	int	idx;
	char	*filename;
	int cmd_nums;
	(void)argc;

	cmd_nums = argc - 3;
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
		cmd_nums--;
	}
	else
		filename = argv[1];


	idx = 0;
	while (idx++ < cmd_nums)
	{
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

				infile_fd = open(filename, O_RDONLY);
				if (infile_fd == -1)
					ft_error("Open Error ", 1014);//exit code
				if (dup2(infile_fd, STDIN_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
			}
			else if (idx == cmd_nums - 1) // last child process
			{
				int	outfile_fd;

				outfile_fd = open(argv[argc - 1], O_RDONLY);
				if (outfile_fd == -1)
					ft_error("Open Error ", 1014);//exit code
				if (dup2(fd[0], STDIN_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				if (dup2(outfile_fd, STDOUT_FILENO) == -1)
					ft_error("Dup2 Error ", 1014);//exit code
				
			}
			else //mid child process
			{
				
			}
		}
		else //Main process
		{

		}
	}


	//if (dup2(fd[0], STDIN_FILENO) == -1)
	//	ft_error("Dup2 Error ", 1014);//exit_code
	//if (dup2(fd[1], STDOUT_FILENO) == -1)
	//	ft_error("Dup2 Error ", 1014);//exit_code



	return (0);
}

//./pipex file1 cmd1 cmd2 cmd3 cmd4 file2
// 1. STDIN을 file1 fd로 dup2한다.
// 2. STDOUT file
// 2. input the text in the file 1 to cmd1
// 3. 