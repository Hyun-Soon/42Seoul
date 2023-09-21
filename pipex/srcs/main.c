/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:22:23 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/21 20:40:56 by hyuim            ###   ########.fr       */
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

// ./pipex here_doc LIMITER cmd cmd1 file
// cmd << LIMITER | cmd1 >> file

int main(int argc, char *argv[])
{
	int	fd[2];
	int	pid;
	int	idx;

	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		char	*gnl_ret;
		int		temp_file_fd;

		// TODO : how to name temp file that isn't same with existing file
		temp_file_fd = open(filename + "tmp", O_RDWR | O_CREAT, 0644);
		while (1)
		{
			gnl_ret = get_next_line(STDIN_FILENO);
			if (!gnl_ret)
			{
				write(2, "Gnl Error\n", 10);
				exit(); //exit_code
			}
			if (ft_strcmp(argv[2], gnl_ret) == 0)
				break ;
			if (write(temp_file_fd, gnl_ret, sizeof(gnl_ret)) == -1)
				ft_error("Write tmp file Error ", );//exit code
		}
	}
<< 
	idx = 0;
	if (pipe(fd) == -1)
		ft_error("Pipe Error ", );//exit_code
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error("Dup2 Error ", );//exit_code
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("Dup2 Error ", );//exit_code
	while (idx++ < argc - 2)
	{
		pid = fork();
		if (pid < 0)
			ft_error("Fork Error ", );//exit_code
		if (pid == 0)
		{
			// Child process
			char *args[];

			execve()
		}
		
	}

	return (0);
}

//./pipex file1 cmd1 cmd2 cmd3 cmd4 file2
// 1. STDIN을 file1 fd로 dup2한다.
// 2. STDOUT file
// 2. input the text in the file 1 to cmd1
// 3. 