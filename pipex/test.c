#include "libft/libft.h"

int main(int argc, char *argv[], char *envp[])
{
	int idx = 2;
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