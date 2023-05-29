#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <errno.h>
#include <string.h>
void err(const char* msg) {
	perror(msg);
	perror(strerror(errno));
	_exit(1);
}

int main() {
	pid_t pid = fork();
	if (-1 == pid) {
		err("open error\n");
	} else if (0 == pid) {
		printf("child pid %d, ppid %d \n", getpid(), getppid());
		sleep(3);
		kill(getppid(), SIGKILL);
	} else {
		while (1) {
			printf("parent pid %d \n", getpid());
			sleep(1);
		}
	}


	return 0;
}
