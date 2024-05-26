# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

# include <stdlib.h>

# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

# include <signal.h>

# include <unistd.h>

void	close_n_dup(int i, int fd[3][2], int last)
{
	// close(fd[i - 1][1]);
	// close(fd[i - 1][0]);
	if (last == 0)
		dup2(fd[i + 1][1], 1);
	close(fd[i][1]);
	dup2(fd[i][0], 0);
	close(fd[i][0]);
}

int main()
{
	char *prog0[] = {"ls", "-l", NULL};
	char *prog1[] = {"grep", "mini", NULL};
	char *prog2[] = {"wc", "-l", NULL};
	char *prog3[] = {"grep", "4", "-c", NULL};
	int fd[3][2];
	int pid_0 = fork();
	if (pid_0 == 0)
	{
		pipe(fd[0]);
		int pid = fork();
		if (pid == 0)
		{
			close(fd[0][0]);
			dup2(fd[0][1], 1);
			close(fd[0][1]);
			if (execve("/bin/ls", prog0, NULL) != 0)
				perror("");
		}
		pipe(fd[1]);
		int pid2 = fork();
		if (pid2 == 0)
		{
			waitpid(pid, NULL, 0);
			close(fd[0][1]);
			dup2(fd[0][0], 0);
			close(fd[0][0]);
			dup2(fd[1][1], 1);
			close(fd[1][1]);
			if (execve("/bin/grep", prog1, NULL) != 0)
				perror("");
		}
		pipe(fd[2]);
		close(fd[0][0]);
		close(fd[0][1]);
		int pid3 = fork();
		if (pid3 == 0)
		{
			close_n_dup(1, fd, 0);
			waitpid(pid2, NULL, 0);
			if (execve("/bin/wc", prog2, NULL) != 0)
				perror("");
		}
		close(fd[1][0]);
		close(fd[1][1]);
		int pid4 = fork();
		if (pid4 == 0)
		{
			close_n_dup(2, fd, 1);
			waitpid(pid3, NULL, 0);
			if (execve("/bin/grep", prog3, NULL) != 0)
				perror("");
		}
		close(fd[2][0]);
		close(fd[2][1]);
		waitpid(pid4, NULL, 0);
		// close(fd[0][1]);
		// close(fd[0][0]);
		// close(fd[1][1]);
		// dup2(fd[1][0], 0);
		// close(fd[1][0]);
		// close_n_dup(1, fd);
		// waitpid(pid2, NULL, 0);
	}
	else
	{
		waitpid(pid_0, NULL, 0);
		printf("my pid is %d\n", getpid());
		printf("the program finished execution\n");
	}
}