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
		while (1) {
			printf("child pid %d, ppid %d \n", getpid(), getppid());
			sleep(1);
		}
	} else {
		printf("parent id %d\n", getpid());
		sleep(3);
		printf("to kill group process\n");
		int ret = kill(0, SIGKILL);
		if (-1 == ret) {
			err("kill error\n");
		}
	}


	return 0;
}
