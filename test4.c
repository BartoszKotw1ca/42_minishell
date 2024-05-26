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

void	close_n_dup(int i, int fd[3][2], int noc)
{
	if (i + 2 != noc)
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
	int noc = 4;
	int pid[noc];
	int fd[noc - 1][2];
	int pid_main = fork();
	if (pid_main == 0)
	{
		int i = 0;
		while (i < noc -1)
			pipe(fd[i++]);

		i = 0;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			close_n_dup(i - 1, fd, noc);
			if (i != 0)
				waitpid(pid[i - 1], NULL, 0);
			if (execve("/bin/ls", prog0, NULL) != 0)
				perror("");
		}
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);

		i = 1;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			close_n_dup(i - 1, fd, noc);
			if (i != 0)
				waitpid(pid[i - 1], NULL, 0);
			if (execve("/bin/grep", prog1, NULL) != 0)
				perror("");
		}
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);

		i = 2;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			close_n_dup(i - 1, fd, noc);
			if (i != 0)
				waitpid(pid[i - 1], NULL, 0);
			if (execve("/bin/wc", prog2, NULL) != 0)
				perror("");
		}
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);

		i = 3;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			close_n_dup(i - 1, fd, noc);
			if (i != 0)
				waitpid(pid[i - 1], NULL, 0);
			if (execve("/bin/grep", prog3, NULL) != 0)
				perror("");
		}
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);

		i = 4;
		waitpid(pid[i - 1], NULL, 0);
	}
	else
	{
		waitpid(pid_main, NULL, 0);
		printf("my pid is %d\n", getpid());
		printf("the program finished execution\n");
	}
}