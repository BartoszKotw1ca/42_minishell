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
	int pid_main = fork();
	if (pid_main == 0)
	{
		pipe(fd[0]);
		pipe(fd[1]);
		pipe(fd[2]);
		int i = 0;
		int pid1 = fork();
		if (pid1 == 0)
		{
			close(fd[0][0]);
			dup2(fd[0][1], 1);
			close(fd[0][1]);
			if (execve("/bin/ls", prog0, NULL) != 0)
				perror("");
		}
		i = 1;
		int pid2 = fork();
		if (pid2 == 0)
		{
			close_n_dup(0, fd, 0);
			waitpid(pid1, NULL, 0);
			// close(fd[0][1]);
			// dup2(fd[0][0], 0);
			// close(fd[0][0]);
			// dup2(fd[1][1], 1);
			// close(fd[1][1]);
			if (execve("/bin/grep", prog1, NULL) != 0)
				perror("");
		}
		close(fd[0][0]);
		close(fd[0][1]);
		i = 2;
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
		i = 3;
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
		i = 4;
		waitpid(pid4, NULL, 0);
	}
	else
	{
		waitpid(pid_main, NULL, 0);
		printf("my pid is %d\n", getpid());
		printf("the program finished execution\n");
	}
}