/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:22:23 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/26 17:04:15 by hyuim            ###   ########.fr       */
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


// TODO :: cmd cnt == 1, O_APPEND
int main(int argc, char *argv[], char *envp[])
{
	int	fd[2]; //fd[0] : read , fd[1] : write
	int	pid;
	int	idx;

	char	*filename;
	int	first_cmd_idx;
	int outfile_flag = O_WRONLY | O_CREAT | O_TRUNC;

	first_cmd_idx = 2;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		char	*gnl_ret;
		int		temp_file_fd;

		outfile_flag = O_WRONLY | O_CREAT | O_APPEND;
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

	if (first_cmd_idx == argc - 2)
	{
		int infile_fd2 = open(filename, O_RDONLY);
		if (infile_fd2 == -1)
			ft_error("Open Error ", 1014);//exit code
		int outfile_fd2 = open(argv[argc - 1], outfile_flag, 0644);
		if (outfile_fd2 == -1)
			ft_error("Open Error ", 1014);//exit code
		if (dup2(infile_fd2, STDIN_FILENO) == -1)
			ft_error("Dup2 Error ", 1014);//exit code
		if (dup2(outfile_fd2, STDOUT_FILENO) == -1)
			ft_error("Dup2 Error ", 1014);//exit code
		close(infile_fd2);
		close(outfile_fd2);

		char **cmd_args = ft_split(argv[first_cmd_idx], ' ');
		//printf("cmd_args : %s\n\n", cmd_args[0]);
		char *envp_path;
		char **split_path;
		int	idx2 = -1;
		split_path = NULL;
		while (envp[++idx2])
		{
			if (ft_strncmp("PATH=", envp[idx2], 5) == 0)
			{
				//printf("envp[idx2] : %s\n\n", envp[idx2]);
				envp_path = ft_strchr(envp[idx2], '=') + 1;
				//printf("envp_path : %s\n\n", envp_path);
				split_path = ft_split(envp_path, ':');
				break ;
			}
		}
		int path_idx = -1;
		execve(cmd_args[0], cmd_args, envp);
		while (split_path[++path_idx])
		{
			char *path_plus_cmd = ft_strjoin(split_path[path_idx], "/");
			path_plus_cmd = ft_strjoin(path_plus_cmd, cmd_args[0]);
			execve(path_plus_cmd, cmd_args, envp);
		}
		ft_error("Cmd not found Error ", 1014);//exit code
	}
	else
	{
		idx = first_cmd_idx - 1;
		while (++idx < argc - 1)
		{
			//if (before_fdread)
			//	closer(before_fdread)
			int	before_fd_read = fd[0];
			if (pipe(fd) == -1)
				ft_error("Pipe Error ", 1014);//exit_code
			pid = fork();
			if (pid < 0)
				ft_error("Fork Error ", 1014);//exit_code
			if (pid == 0)
			{
				// Child process

				char **cmd_args = ft_split(argv[idx], ' ');
				//printf("cmd_args : %s\n\n", cmd_args[0]);
				char *envp_path;
				char **split_path;
				int	idx2 = -1;
				split_path = NULL;
				while (envp[++idx2])
				{
					if (ft_strncmp("PATH=", envp[idx2], 5) == 0)
					{
						//printf("envp[idx2] : %s\n\n", envp[idx2]);
						envp_path = ft_strchr(envp[idx2], '=') + 1;
						//printf("envp_path : %s\n\n", envp_path);
						split_path = ft_split(envp_path, ':');
						break ;
					}
				}
				//printf("split_path : %s\n", split_path[0]);
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
					close(infile_fd);
				}
				else if (idx == argc - 2) // last child process
				{
					int	outfile_fd;

					close(fd[0]);
					close(fd[1]);
					outfile_fd = open(argv[argc - 1], outfile_flag, 0644);
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
				int path_idx = -1;
				execve(cmd_args[0], cmd_args, envp);
				while (split_path[++path_idx])
				{
					char *path_plus_cmd = ft_strjoin(split_path[path_idx], "/");
					path_plus_cmd = ft_strjoin(path_plus_cmd, cmd_args[0]);
					execve(path_plus_cmd, cmd_args, envp);
				}
				ft_error("Cmd not found Error ", 1014);//exit code
			}
			close(fd[1]);
		}
	}


	int	idx3 = first_cmd_idx - 1;
	while (++idx3 < argc - 1)
		if (wait(0) == -1)
			ft_error("Wait Error ", 1014);//exit code
	return (0);
}
