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

int main()
{
	char *prog0[] = {"ls", "-l", NULL};
	char *prog1[] = {"grep", "test", NULL};
	int fd[2][2];
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
		waitpid(pid, NULL, 0);
		close(fd[0][1]);
		dup2(fd[0][0], 0);
		close(fd[0][0]);
		if (execve("/bin/grep", prog1, NULL) != 0)
			perror("");
	}
	waitpid(pid_0, NULL, 0);
	printf("the program finished execution\n");
}